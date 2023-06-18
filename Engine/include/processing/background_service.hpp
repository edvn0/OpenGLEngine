#pragma once

#include "common/logger.hpp"
#include "common/types.hpp"

#include <array>
#include <chrono>
#include <cstdint>
#include <functional>
#include <mutex>
#include <queue>
#include <string_view>
#include <thread>
#include <type_traits>

namespace Engine::Background {

	using BackgroundFunction = std::function<void(std::thread::id)>;
	using SomeOtherBackgroundFunction = std::function<void(std::thread::id, std::string_view)>;

	enum class TaskPriority { Low = 0, Mid = 1, High = 2, Instant = 3 };

	template <class Func> struct BasicBackgroundTask {
		Func function;
		TaskPriority priority;
	};

	namespace {
		template <std::uint32_t Interval, std::size_t Threads, class Func, template <class> class Task> class BasicBackgroundService {
			using BBS = BasicBackgroundService<Interval, Threads, Func, Task>;

			static constexpr auto evaluate_function = [](const Func& f) {
				const auto this_id = std::this_thread::get_id();
				if constexpr (std::is_same_v<Func, BackgroundFunction>)
					f(this_id);

				if constexpr (std::is_same_v<Func, SomeOtherBackgroundFunction>)
					f(this_id, "Hello");
			};

		public:
			BasicBackgroundService() = default;
			~BasicBackgroundService()
			{
				stop_flag = true;
				stop();
			}

			auto submit(Func&& f, TaskPriority prio = TaskPriority::Mid) -> void
			{
				logger.info("Pushed a lambda with priority {}", static_cast<int>(prio));
				if (prio != TaskPriority::Instant)
					tasks.push(Task<Func> { .function = std::move(f), .priority = prio });
				else {
					evaluate_function(std::move(f));
				}
			}

			void start_processing()
			{
				if (started)
					return;

				for (std::size_t i = 0; i < Threads; i++) {
					processors[i] = std::thread(&BBS::process_tasks, this);
				}

				started = true;
			}

			void stop()
			{
				for (auto& processor : processors)
					processor.join();

				std::scoped_lock lock(task_mutex);
				if (!tasks.empty()) {
					logger.info("Running the final {} tasks.", tasks.size());
					while (!tasks.empty()) {
						const auto popped = tasks.top();
						tasks.pop();
						evaluate_function(popped.function);
					}
					logger.info("Successfully ran the last tasks.");
				}
			}

		private:
			template <typename T> struct Priority {
				bool operator()(const T& l, const T& r) const { return r.priority > l.priority; }
			};
			using QueueItem = Task<Func>;
			using QueueVector = std::vector<QueueItem>;
			using QueueComparator = Priority<QueueItem>;
			using TaskQueue = std::priority_queue<QueueItem, QueueVector, QueueComparator>;
			TaskQueue tasks;

			void process_tasks()
			{
				while (!stop_flag) {
					std::this_thread::sleep_for(std::chrono::duration<float, std::milli>(Interval));
					std::scoped_lock lock(task_mutex);

					if (tasks.empty())
						continue;

					const auto popped = tasks.top();
					tasks.pop();
					evaluate_function(popped.function);
				}
			}

			Logging::Logger logger { "BackgroundService" };
			std::array<std::thread, Threads> processors;
			std::atomic_bool stop_flag;
			std::mutex task_mutex;
			bool started { false };
		};

	} // namespace

	using BackgroundService = BasicBackgroundService<100, 4, BackgroundFunction, BasicBackgroundTask>;
	using SomeOtherBackgroundService = BasicBackgroundService<100, 4, SomeOtherBackgroundFunction, BasicBackgroundTask>;

	void submit_work(BackgroundFunction&& f, TaskPriority prio = TaskPriority::Mid);

	void submit_work(SomeOtherBackgroundFunction&& f, TaskPriority prio = TaskPriority::Mid);

} // namespace Engine::Background
