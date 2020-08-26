#ifndef DEQUE_H
#define DEQUE_H

#include <iostream>
	using std::string;
	using std::cout;
	using std::ostream;

/**
 * DequeException is an exception that is thrown when
 * an illegal action on the Deque is performed.
 */
class DequeException {
	private :
		string m_location;
		string m_message;
	public :
		/**
		 * Creates an exception to throw.
		 * @param where_thrown The name of the function that throws the exception.
		 * @param msg The message that explains the reason for the exception.
		 */
		DequeException(const string & where_thrown, const string & msg) {
			m_location = where_thrown;
			m_message = msg;
		}
		/**
		 * @return A string that provides the information of the exception.
		 */
		string to_string() const {
			return "*** StackException in "+
				m_location + ": "+m_message;
		}
};

template<class E>
/**
 * Deque is a doubly-ended Queue.
 * It provides all the functionality of both a Stack and Queue abstract data type.
 * The elements in the Deque are determined by the user when an object is instantiated.
 */

class Deque {
	private :
		// private inner class
		/** 
		 * The Node class is the standard doubly-linked node that contains elements of type E.
		 * This class is only accessible to the Deque.
		 */
		class Node {
			public:
				E element;
				Node * next;
				Node * prev;
			
				Node(const E &value, Node * nxt=nullptr, Node * prv=nullptr) {
					element = value;
					next = nxt;
					prev = prv;
				}
		};

		Node * first;
		Node * last;
		int m_size;

		/**
		 * Inserts an element into the Deque that would be the first position in the Queue,
		 * and / or the bottom of the Stack.
		 * Since this is not part of either ADT, this function is private and used as a helper
		 * function.
		 */
		void insert_first(E element) { 
			first = new Node(element,first);
			if (is_empty()) {
				last = first;
			} else {
				first->next->prev = first;
			}
			m_size++;
		}

	public:
	/*******************  Constructors / Destructors ***************/
		/**
		 * Creates an empty Deque object.
		 */
		Deque() {
			first = last = nullptr;
			m_size = 0;
		}

		/**
		 * Removes all elements from the Deque,
		 * freeing up any memory that was allocated.
		 */
		~Deque() {
			while (first) {
				dequeue();
			}
		}

		/**
		 * Creates a hard-copy of a Deque.
		 * @param copy The Deque to copy.
		 */
		Deque( const Deque<E> &copy) {
			// This hard copy is necessary as Deque is returned as a parameter.
			m_size = 0;
			Node * tmp = copy.first;
			while (tmp) {
				push(tmp->element);
				tmp = tmp->next;
			}
		}

		/******************  Queue and Stack behaviour  *****************/

		/**
		 * Retrieves but does not remove the element at the top of the stack.
		 * @return The top element.
		 * @throw DequeException if the stack is empty.
		 */
		E top() const {
			if (is_empty()) {
				throw DequeException("get_last", "Stack is empty");
			}
			return last->element;
		}

		/**
		 * Retrieves but does not remove the element at the front of the queue.
		 * @return the front element.
		 * @throw DequeException if the queue is empty.
		 */
		E front() const {
			if (is_empty()) {
				throw DequeException("front", "Queue is empty");
			}
			return first->element;
		}
	
		/**
		 * @return true if the stack/queue is empty, false if it is not.
		 */
		bool is_empty() const {
			return m_size == 0;
		}

		/******************  Inserting **********************/
		/**
		 * Inserts an element to the back of the queue.
		 * @param element The newly inserted element.
		 */
		void enqueue(E element) {
			last = new Node(element,nullptr,last);
			if (is_empty()) {
				first = last;
			} else {
				last->prev->next = last;
			}
			m_size++;
		}

		/**
		 * Inserts an element onto the top of the stack.
		 * @param element The newly inserted element.
		 */
		void push(E element) {
			enqueue(element);
		};

		/*****************  Removing ***********************/
		/**
		 * Removes the element at the front of the queue.
		 * @return The element that was removed.
		 * @throw DequeException if the queue is empty.
		 */
		E dequeue() {
			if (is_empty()) {
				throw DequeException("dequeue","Queue is empty");
			}
			Node * tmp = first;
			E to_return = tmp->element;
			first = first->next;
			if (first) {
				first->prev = nullptr;
			} else {
				last = nullptr;  // we just removed the last one.
			}
			delete tmp;
			m_size--;
			return to_return;
		}
	
		/**
		 * Removes the element at the top of the stack.
		 * @return The element that was removed.
		 * @throw DequeException if the stack is empty.
		 */
		E pop() {
			if (is_empty()) {
				throw DequeException("pop","Stack is empty");
			}
			if (m_size==1) {
				return dequeue();
			}
			Node * tmp = last;
			E to_return = tmp->element;
			last = last->prev;
			last->next = nullptr;
			delete tmp;
			m_size--;

			return to_return;
		}
	
		/**************** For debugging ***********************/
		// The following are not part of the Stack or Queue ADT,
		// but are helpful for debugging during programming.

		/**
		 * Prints out the contents of the list from in queue order.
		 * 	Format : all one line, with a space between each element.
		 */
		void print_queue() const {
			if (is_empty()) {
				cout << "Queue is empty.\n";
			} else {
				for (Node * tmp = first; tmp; tmp=tmp->next) {
					cout << tmp->element << " ";
				}
			}
		}

		/**
		 * Prints out the contents of the list from in stack order.
		 * 	Format : all one line, with a space between each element.
		 */
		void print_stack() const {
			if (is_empty()) {
				cout << "Stack is empty.\n";
			} else {
				for (Node * tmp = last; tmp; tmp=tmp->prev) {
					cout << tmp->element << " ";
				}
			}
		}

};





#endif

