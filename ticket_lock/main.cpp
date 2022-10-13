#include <mutex>
#include <condition_variable>
#include <iostream>

struct Node {
	Node(size_t num) : next(nullptr), ticket_number(num) {}
	Node* next;
	size_t ticket_number;
};

#pragma once

namespace spinlocks {

/*  Scalable Queue SpinLock
 *
 *  Usage:
 *
 *  QueueSpinLock qspinlock;
 *  {
 *    QueueSpinLock::Guard guard(qspinlock);  // <-- Acquire
 *    // Critical section
 *  }  // <-- Release
 */

	class QueueSpinLock {
	public:
		class Guard {
			friend class QueueSpinLock;

		public:
			explicit Guard(QueueSpinLock& spinlock) : spinlock_(spinlock) {
				spinlock_.Acquire(this);
			}

			~Guard() {
				spinlock_.Release(this);
			}

		private:
			QueueSpinLock& spinlock_;
			// ???
		};

	private:
		void Acquire(Guard* /*guard*/) {
			// Your code goes here
		}

		void Release(Guard* /*owner*/) {
			// Your code goes here
		}

	private:
		// ???
	};

}  // namespace spinlocks