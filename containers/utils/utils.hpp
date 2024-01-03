/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdarkhaw <fdarkhaw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 18:25:12 by fdarkhaw          #+#    #+#             */
/*   Updated: 2022/12/25 22:34:57 by fdarkhaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include <cstddef>
# include <limits>
# include <sstream>
# include <typeinfo>
# include <iostream>

/*
   Type of the null pointer constant.
   Permetted implicit conversions to null pointer ,
   similary conversions for all type of contant null pointer.
**
   From : (Take a look)
   https://www.amazon.com/dp/0201924889
*/
static class nullptr_t
{
	public:
		/*
		   For conversion to any type
		   of null non-member pointer.
		*/
		template<class T>
		operator T*() const { return (0); }

		/*
		   For conversion to any type of null
		   member pointer.
		*/
		template<class C, class T>
		operator T C::*() const { return (0); }

	private:

		/*
		   It's imposible to get an address of
		   a nullptr.
		*/
		void operator&() const;

} u_nullptr = {};

namespace ft
{
	/*
	   Transfom "n" to std::string.
	**
	   n the object to convert. (Sure for
	   classic number types).
		return Converted "n".

	   Take a look:
	   http://www.cplusplus.com/articles/D9j2Nwbp/
	*/
	template <typename T>
		std::string to_string(T n)
		{
			/* Stream used to convert */
			std::ostringstream ss;
			ss << n;
			return (ss.str());
		}

	/*
	   Base class for standard binary function objects.
	   (Doc = http://www.cplusplus.com/reference/functional/binary_function/?kw=binary_function)
	   It have no operator "()" like functin objects,
	   it is up to the class deriving from it to define it.
	   It just has 3 public data memebers that are typedefs of the
	   template parameters.
	   (the operator "()", permet to use a class with the same syntax
	   as a function call).
	*/
	template <class Arg1, class Arg2, class Result>
		struct binary_function
		{
			/* The first argument type */
			typedef Arg1 first_argument_type;

			/* The second arguement type */
			typedef Arg2 second_argument_type;

			/* The result type */
			typedef Result result_type;
		};

	/*
	   A binary function object class who will return
	   whether the first arguement compares less than the second.
	   (using "<" operator).
	*/
	template <class T>
		struct less : binary_function<T, T, bool>
		{
			bool operator() (const T& x, const T& y) const { return (x < y); }
		};

	/*
	   Couple a pair of values, which may be of different types
	   (T1 and T2)
	*/
	template <class T1, class T2>
		struct pair
		{
			public :
				typedef T1 first_type;
				typedef T2 second_type;
				first_type first;
				second_type second;

				// Constructor
				pair()
				:
					first(),
					second()
				{}

				// Copy
				template<class U, class V>
					pair (const pair<U, V>& pr)
					:
						first(pr.first),
						second(pr.second)
					{}

				// Initialization
				pair (const first_type& a, const second_type& b)
				:
					first(a),
					second(b)
				{}

				pair& operator= (const pair& pr)
				{
					if (*this == pr)
						return (*this);
					this->first = pr.first;
					this->second = pr.second;
					return (*this);
				}
		};

	template <class T1, class T2>
		bool operator== (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
		{
			return (lhs.first == rhs.first && lhs.second == rhs.second);
		}

	template <class T1, class T2>
		bool operator!= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
		{
			return !(lhs == rhs);
		}

	template <class T1, class T2>
		bool operator<  (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
		{
			return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
		}

	template <class T1, class T2>
		bool operator<= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
		{
			return !(rhs < lhs);
		}

	template <class T1, class T2>
		bool operator>  (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
		{
			return (rhs < lhs);
		}

	template <class T1, class T2>
		bool operator>= (const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs)
		{
			return !(lhs < rhs);
		}

	template <class T1, class T2>
		ft::pair<T1,T2> make_pair(T1 x, T2 y)
		{
			return (ft::pair<T1, T2>(x, y));
		}

	template<bool Cond, class T = void> struct enable_if {};
	template<class T> struct enable_if<true, T> { typedef T type; };

	// All the next part is an adaptation of is_integral.
	// "is_integral" for this project in C++98 is a structure
	// that contain if the type given to it is a type from this list :
	//  - bool
	//  - char
	//  - char16_t
	//  - char32_t
	//  - wchar_t
	//  - signed char
	//  - short int
	//  - int
	//  - long int
	//  - long long int
	//  - unsigned char
	//  - unsigned short int
	//  - unsigned int
	//  - unsigned long int
	//  - unsigned long long int

	template <bool is_integral, typename T>
		struct is_integral_res {
			typedef T type;
			static const bool value = is_integral;
			};

	template <typename>
		struct is_integral_type : public is_integral_res<false, bool> {};

	template <>
		struct is_integral_type<bool> : public is_integral_res<true, bool> {};

	template <>
		struct is_integral_type<char> : public is_integral_res<true, char> {};

	template <>
		struct is_integral_type<signed char> : public is_integral_res<true, signed char> {};

	template <>
		struct is_integral_type<short int> : public is_integral_res<true, short int> {};

	template <>
		struct is_integral_type<int> : public is_integral_res<true, int> {};

	template <>
		struct is_integral_type<long int> : public is_integral_res<true, long int> {};

	template <>
		struct is_integral_type<long long int> : public is_integral_res<true, long long int> {};

	template <>
		struct is_integral_type<unsigned char> : public is_integral_res<true, unsigned char> {};

	/* is_integral_type for unsigned short int. "value is true".*/
	template <>
		struct is_integral_type<unsigned short int> : public is_integral_res<true, unsigned short int> {};

	/* is_integral_type for unsigned int. "value is true".*/
	template <>
		struct is_integral_type<unsigned int> : public is_integral_res<true, unsigned int> {};

	/* is_integral_type for unsigned long int. "value is true".*/
	template <>
		struct is_integral_type<unsigned long int> : public is_integral_res<true, unsigned long int> {};

	/* is_integral_type for unsigned long long int. "value is true".*/
	template <>
		struct is_integral_type<unsigned long long int> : public is_integral_res<true, unsigned long long int> {};

	/*
	   Give a structure who contain is the
	   typename given in template is integral or not,
	   stocked in "value".
	*/
	template <typename T>
		struct is_integral : public is_integral_type<T> { };

	/*  End of is_integral. */

	/*
	   Empty class to identify the category of an
	   "random access iterator". This type of iterator is the
	   most complete iterators. Is particularity is that, it
	   allow to access elements at an arbitrary offset.
	   Take a look :
	   http://www.cplusplus.com/reference/iterator/RandomAccessIterator/
	*/
	class random_access_iterator_tag { };

	/*
	   Empty class to identify the category of an
	   "bidirectional iterator". Bidirectional can be used to access
	   the sequence of elements in a range in both directions.
	   Take a look :
	   http://www.cplusplus.com/reference/iterator/BidirectionalIterator/
	*/
	class bidirectional_iterator_tag { };

	/*
	   Empty class to identify the category of an
	   "forward iterator". Forward iterator can be used to
	   access the sequence of elements in a range in the direction
	   that goes (begin to end).
	   Take a look :
	   http://www.cplusplus.com/reference/iterator/ForwardIterator/
	*/
	class forward_iterator_tag { };

	/*
	   Empty class to identify the category of an
	   "input iterator". Input iterator can be used in sequential
	   input operations, values are read only once and the iterator
	   is icremented.
	   Take a look :
	   http://www.cplusplus.com/reference/iterator/InputIterator/
	*/
	class input_iterator_tag { };

	/*
	   Empty class to identify the category of an
	   "output iterator". Output iterator can be used in sequential
	   output operations, values pointed by the iterator is written
	   a value only once and the iterator is incremented.
	   Take a look :
	   http://www.cplusplus.com/reference/iterator/OutputIterator/
	*/
	class output_iterator_tag { };

	/*
	   Validity of an iterator from is tag.
	   This is the base struct for all is_..._iterator_tag.
	   A boolean is defined by the template and saved in
	   structure. Type too.
	*/
	template <bool is_valid, typename T>
		struct valid_iterator_tag_res { typedef T type; const static bool value = is_valid; };

	/*
	   Basic to check if the typename given
	   is an input_iterator. Based on valid_iterator_tag_res.
	   In this if the typename is not from the possible
	   input iterator form, validity is set to false.
	*/
	template <typename T>
		struct is_input_iterator_tagged : public valid_iterator_tag_res<false, T> { };

	/* Check is_input_iterator_tagged from ft::random_access_iterator_tag */
	template <>
		struct is_input_iterator_tagged<ft::random_access_iterator_tag>
			: public valid_iterator_tag_res<true, ft::random_access_iterator_tag> { };

	/* Check is_input_iterator_tagged from ft::bidirectional_iterator_tag */
	template <>
		struct is_input_iterator_tagged<ft::bidirectional_iterator_tag>
			: public valid_iterator_tag_res<true, ft::bidirectional_iterator_tag> { };

	/* Check is_input_iterator_tagged from ft::forward_iterator_tag */
	template <>
		struct is_input_iterator_tagged<ft::forward_iterator_tag>
			: public valid_iterator_tag_res<true, ft::forward_iterator_tag> { };

	/* Check is_input_iterator_tagged from ft::input_iterator_tag */
	template <>
		struct is_input_iterator_tagged<ft::input_iterator_tag>
			: public valid_iterator_tag_res<true, ft::input_iterator_tag> { };


	/*
	   This will return a structure
	   that contain a boolean "value" true if the
	   iterator given is tagged with a ft iterator
	   tag, otherwise "value" is false.
	*/
	template <typename T>
		struct is_ft_iterator_tagged : public valid_iterator_tag_res<false, T> { };

	/* Check is_ft_iterator_tagged from ft::random_access_iterator_tag */
	template <>
		struct is_ft_iterator_tagged<ft::random_access_iterator_tag>
			: public valid_iterator_tag_res<true, ft::random_access_iterator_tag> { };

	/* Check is_ft_iterator_tagged from ft::bidirectional_iterator_tag */
	template <>
		struct is_ft_iterator_tagged<ft::bidirectional_iterator_tag>
			: public valid_iterator_tag_res<true, ft::bidirectional_iterator_tag> { };

	/* Check is_ft_iterator_tagged from ft::forward_iterator_tag */
	template <>
		struct is_ft_iterator_tagged<ft::forward_iterator_tag>
			: public valid_iterator_tag_res<true, ft::forward_iterator_tag> { };

	/* Check is_ft_iterator_tagged from ft::input_iterator_tag */
	template <>
		struct is_ft_iterator_tagged<ft::input_iterator_tag>
			: public valid_iterator_tag_res<true, ft::input_iterator_tag> { };

	/* Check is_ft_iterator_tagged from ft::output_iterator_tag */
	template <>
		struct is_ft_iterator_tagged<ft::output_iterator_tag>
			: public valid_iterator_tag_res<true, ft::output_iterator_tag> { };

	/*
	   Invalid iterator Exception.
	   Based on std::exception. Called when
	   the iterator tested does not meet demand.
	*/
	template <typename T>
	class InvalidIteratorException : public std::exception
	{
		private:
			std::string _msg;

		public :
			InvalidIteratorException () throw() { _msg = "Is invalid iterator tag : " + std::string(typeid(T).name()); }
			InvalidIteratorException (const InvalidIteratorException&) throw() {}
			InvalidIteratorException& operator= (const InvalidIteratorException&) throw() {}
			virtual ~InvalidIteratorException() throw() {}
			virtual const char* what() const throw() { return (_msg.c_str()); }
	};

	/*
	   Iterator traits class defining properties of
	   iterators. In this, iterator_traits obtains information
	   from Iterator class in template argument.
	*/
	template <class Iterator> struct iterator_traits
	{
		/* Result of subtracting one iterator from another, from Iterator. */
		typedef typename Iterator::difference_type       difference_type;

		/* Type of the element where iterator point, from Iterator. */
		typedef typename Iterator::value_type            value_type;

		/* Type of a pointer to an element where the iterator point, from Iterator. */
		typedef typename Iterator::pointer               pointer;

		/* Type of a reference where iterator point, from Iterator. */
		typedef typename Iterator::reference             reference;

		/* The iterator category from Iterator. */
		typedef typename Iterator::iterator_category     iterator_category;
	};

	/*
	   Iterator traits class defining properties of
	   iterators. This create a default operation with an
	   object (first argument in tempate argument).
	*/
	template <class T> struct iterator_traits<T*>
	{
		/* Result of subtracting one iterator from another. */
		typedef ptrdiff_t                       difference_type;

		/* Type of the element where iterator point. */
		typedef T                               value_type;

		/* Type of a pointer to an element where the iterator point. */
		typedef T*                              pointer;

		/* Type of a reference where iterator point. */
		typedef T&                              reference;

		/* The iterator category from Iterator. */
		typedef ft::random_access_iterator_tag  iterator_category;
	};

	/*
	   Iterator traits class defining properties of
	   iterators. This create a default operation with a
	   const object (first argument in tempate argument).
	*/
	template <class T> class iterator_traits<const T*>
	{
		/* Result of subtracting one iterator from another. */
		typedef ptrdiff_t                       difference_type;

		/* Type of the element where iterator point. */
		typedef T                               value_type;

		/* Type of a pointer to an element where the iterator point. */
		typedef const T*                        pointer;

		/* Type of a reference where iterator point. */
		typedef const T&                        reference;

		/* The iterator category from Iterator. */
		typedef ft::random_access_iterator_tag  iterator_category;
	};

	/*
	   Give a difference_type defined in ft::iterator_traits
	   that's the difference of address in memory
	   between last and first iterator.
	**
	   first The first iterator.
	   last The last iterator.
		return The difference.
	*/
	template<class InputIterator>
		typename ft::iterator_traits<InputIterator>::difference_type
			distance (InputIterator first, InputIterator last)
		{
			typename ft::iterator_traits<InputIterator>::difference_type rtn = 0;
			while (first != last)
			{
				first++;
				rtn++;
			}
			return (rtn);
		}

	/*
	   Base class for iterator, not really usefull, but type
	   defined can be use for iterator_traits. An iterator permeted to
	   take any element range in an object and using a set of operators.
	*/
	template <class Category, class T, class Distance = ptrdiff_t,
		class Pointer = T*, class Reference = T&>
		class iterator
		{
			public:
				/* Type of elements pointed. */
				typedef T           value_type;

				/* Type to represent the difference between two iterators. */
				typedef Distance    difference_type;

				/* Type to represent a pointer to an element pointed */
				typedef Pointer     pointer;

				/* Type to represent a reference to an element pointed */
				typedef Reference   reference;

				/* Category of the iterator. */
				typedef Category    iterator_category;
		};

	template <class T>
		class bidirectional_iterator : ft::iterator<ft::bidirectional_iterator_tag, T>
		{
			/* Category of the iterator. */
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category     iterator_category;

			/* Type of elements pointed. */
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::value_type            value_type;

			/* Type to represent the difference between two iterators. */
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type       difference_type;

			/* Type to represent a pointer to an element pointed */
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::pointer               pointer;

			/* Type to represent a reference to an element pointed */
			typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::reference             reference;

			private:
				/* Element pointed by the iterator. */
				pointer _elem;
		};

	template <class Iterator>
	class reverse_iterator
	{
		public:

			/* Iterator's type. */
			typedef Iterator    iterator_type;

			/* Preserves Iterator's category. */
			typedef typename ft::iterator_traits<Iterator>::iterator_category iterator_category;

			/* Preserves Iterator's value type. */
			typedef typename ft::iterator_traits<Iterator>::value_type      value_type;

			/* Preserves Iterator's difference type. */
			typedef typename ft::iterator_traits<Iterator>::difference_type     difference_type;

			/* Preserves Iterator's pointer. */
			typedef typename ft::iterator_traits<Iterator>::pointer     pointer;

			/* Preserves Iterator's reference. */
			typedef typename ft::iterator_traits<Iterator>::reference   reference;

			/*
			   Default.
			   Construct a reverse iterator object.
			   This will points to no object.
			*/
			reverse_iterator()
			:
				_elem()
			{}

			/*
			   Initialization.
			   Construct a reverse iterator object from
			   an original iteretor "it".
			   The behavior of the constructed object
			   replicate the orignal, but he iterates
			   in the reverse order.
			**
			   it The iterator to replicate.
			*/
			explicit reverse_iterator (iterator_type it)
			:
				_elem(it)
			{}

			/*
			   Copy.
			   Contruct a reverse iterator from other reverse iterator.
			   Save the sense of iterateration as "rev_it".
			**
			   rev_it original reverse iterator.
			*/
			template <class Iter>
				reverse_iterator (const reverse_iterator<Iter>& rev_it)
				:
					_elem(rev_it.base())
				{}

			/* Added to follow subject obligation */
			virtual ~reverse_iterator() {}

			/*
			   Return a copy of the base iterator.
			   Same type as the usert to construct the reverse_iterator.
			   But pointing to the element next of this.
			   (A reverse iterator always pointing to an element at
			   an offset of -1).
			**
				return A copy of the base iterator.
			*/
			iterator_type base() const
			{ return (_elem); }

			/*
			   Return a reference to the element pointed
			   by the iterator.
			**
				return The reference.
			*/
			reference operator*() const
			{
				iterator_type tmp = _elem;
				return (*(--tmp));
			}

			/*
			   Return a reverse iterator pointing to
			   the element at n position away from the pointed
			   element of the iterator.
			   This function need the base iterator to be a
			   "random-access iterator".
			**
			   "n" Number of elements to offset.
				return An iterator pointing to the element at "n"
			   position away.
			*/
			reverse_iterator operator+ (difference_type n) const { return (reverse_iterator(_elem - n)); }

			/*
			   Advances the reverse_iterator by one position.
			   Pre-increment.
			**
				return return "(*this)" incremented.
			*/
			reverse_iterator& operator++()
			{
				--_elem;
				return (*this);
			}

			/*
			   Advances the reverse_iterator by one position.
			   Post-increment.
			**
				return the value "(*this)" value had before the
			   call.
			*/
			reverse_iterator operator++(int)
			{
				reverse_iterator tmp = *this;
				++(*this);
				return (tmp);
			}

			/*
			   Advances the "reverse_iterator" by n element positions.
			   This function need the base iterator to be a
			   "random-access iterator".
			**
			   n the number of element.
				return the reverse iterator itself (*this).
			*/
			reverse_iterator& operator+= (difference_type n)
			{
				_elem -= n;
				return (*this);
			}

			/*
			   Return a reverse iterator pointing to the element
			   located n positions before the element the iterator
			   currently points to.
			   This function need the base iterator to be a
			   "random-access iterator".
			**
			   n the number of element.
				return An iterator pointing to the element
			   n position before the currently pointed one.
			*/
			reverse_iterator operator- (difference_type n) const { return (reverse_iterator(_elem + n)); }

			/*
			   Decreases the reverse iterator by one position.
			**
				return "(*this)".
			*/
			reverse_iterator& operator--()
			{
				++_elem;
				return (*this);
			}

			/*
			   Decreases the reverse iterator by one position.
			**
				retun "(*this)" value before the call.
			*/
			reverse_iterator operator--(int)
			{
				reverse_iterator tmp = *this;
				--(*this);
				return (tmp);
			}

			/*
			   Decreases the reverse iterator by "n" element
			   postion.
			   This function need the base iterator to be a
			   "random-access iterator".
			**
			   n Number of elements to offset.
				return "(*this)".
			*/
			reverse_iterator& operator-= (difference_type n)
			{
				_elem += n;
				return (*this);
			}

			/*
			   Give a pointer to the element
			   pointed.
			**
				return A pointer to the element pointed.
			*/
			pointer operator->() const { return &(operator*()); }

			/*
			   Accesse the element at "n" positions
			   away from the element currently pointed.
			   Cause undefined behavior if the element
			   does not exist.
			**
			   n The number of positions.
				return A reference at "n".
			*/
			reference operator[] (difference_type n) const { return (this->base()[-n - 1]); }

		private:
			iterator_type     _elem;
	};

	/*
	   Equal comparison between two reverse iterator.
	**
	   lhs Base of comparison.
	   rhs To compare with "lsh".
		return True if the condition is hold, otherwise false.
	*/
	template <class Iterator>
		bool operator== (const reverse_iterator<Iterator>& lhs,
						const reverse_iterator<Iterator>& rhs) { return (lhs.base() == rhs.base()); }

	/* For reverser_iterator == const_reverse_iterator */
	template <class Iterator_L, class Iterator_R>
		bool operator== (const reverse_iterator<Iterator_L>& lhs,
						const reverse_iterator<Iterator_R>& rhs) { return (lhs.base() == rhs.base()); }

	/*
	   Different comparison between two reverse iterator.
	**
	   lhs Base of comparison.
	   rhs To compare with "lsh".
		return True if the condition is hold, otherwise false.
	*/
	template <class Iterator>
		bool operator!= (const reverse_iterator<Iterator>& lhs,
						const reverse_iterator<Iterator>& rhs) { return (lhs.base() != rhs.base()); }

	/* For reverser_iterator != const_reverse_iterator */
	template <class Iterator_L, class Iterator_R>
		bool operator!= (const reverse_iterator<Iterator_L>& lhs,
						const reverse_iterator<Iterator_R>& rhs) { return (lhs.base() != rhs.base()); }

	/*
	   Inferior comparison between two reverse iterator.
	**
	   lhs Base of comparison.
	   rhs To compare with "lsh".
		return True if the condition is hold, otherwise false.
	*/
	template <class Iterator>
		bool operator<  (const reverse_iterator<Iterator>& lhs,
						const reverse_iterator<Iterator>& rhs) { return (lhs.base() > rhs.base()); }

	/* For reverser_iterator < const_reverse_iterator */
	template <class Iterator_L, class Iterator_R>
		bool operator< (const reverse_iterator<Iterator_L>& lhs,
						const reverse_iterator<Iterator_R>& rhs) { return (lhs.base() > rhs.base()); }

	/*
	   Inferior or equal comparison between two reverse iterator.
	**
	   lhs Base of comparison.
	   rhs To compare with "lsh".
		return True if the condition is hold, otherwise false.
	*/
	template <class Iterator>
		bool operator<= (const reverse_iterator<Iterator>& lhs,
						const reverse_iterator<Iterator>& rhs) { return (lhs.base() >= rhs.base()); }

	/* For reverser_iterator <= const_reverse_iterator */
	template <class Iterator_L, class Iterator_R>
		bool operator<= (const reverse_iterator<Iterator_L>& lhs,
						const reverse_iterator<Iterator_R>& rhs) { return (lhs.base() >= rhs.base()); }

	/*
	   Superior comparison between two reverse iterator.
	**
	   lhs Base of comparison.
	   rhs To compare with "lsh".
		return True if the condition is hold, otherwise false.
	*/
	template <class Iterator>
		bool operator> (const reverse_iterator<Iterator>& lhs,
						const reverse_iterator<Iterator>& rhs) { return (lhs.base() < rhs.bash()); }

	/* For reverser_iterator > const_reverse_iterator */
	template <class Iterator_L, class Iterator_R>
		bool operator> (const reverse_iterator<Iterator_L>& lhs,
						const reverse_iterator<Iterator_R>& rhs) { return (lhs.base() < rhs.base()); }
	/*
	   Superior or equal comparison between two reverse iterator.
	**
	   lhs Base of comparison.
	   rhs To compare with "lsh".
		return True if the condition is hold, otherwise false.
	*/
	template <class Iterator>
		bool operator>= (const reverse_iterator<Iterator>& lhs,
						const reverse_iterator<Iterator>& rhs) { return (lhs.base() <= rhs.base()); }

	/* For reverser_iterator >= const_reverse_iterator */
	template <class Iterator_L, class Iterator_R>
		bool operator>= (const reverse_iterator<Iterator_L>& lhs,
						const reverse_iterator<Iterator_R>& rhs) { return (lhs.base() <= rhs.base()); }

	/*
	   Give a reverse iterator pointing to
	   "rev_it" plus "n".
	**
	   n The number of location away the element pointed
	   by rev_it.
	   rev_it The reverse iterator.
		return A reverse iterator pointing to n element
	   after rev_it pointed element.
	*/
	template <class Iterator>
		reverse_iterator<Iterator> operator+ (
			typename reverse_iterator<Iterator>::difference_type n,
			const reverse_iterator<Iterator>& rev_it) { return (rev_it + n); }

	/*
	   The distance between lhs and rhs.
	**
	   lhs Base of comparison.
	   rhs To compare with "lsh".
		return The number of elements between lsh and rhs.
	*/
	template <class Iterator>
		typename reverse_iterator<Iterator>::difference_type operator- (
			const reverse_iterator<Iterator>& lhs,
			const reverse_iterator<Iterator>& rhs) { return (lhs.base() - rhs.base()); }

	/* For reverser_iterator - const_reverse_iterator */
	template <class Iterator_L, class Iterator_R>
		bool operator- (const reverse_iterator<Iterator_L>& lhs,
						const reverse_iterator<Iterator_R>& rhs) { return (lhs.base() - rhs.base()); }

	/* Lexicographical comparison */

	/*
	   Return true if the range [first1, last2) compare
	   lexicographically lest than the range [first2, last2).
	**
	   first1, last1 the start and the end of the first range.
	   first2, last2 the start and the end of the second range.
		return true if the first range compares lexicographically less
	   than the second, false otherwise.
	*/
	template <class InputIterator1, class InputIterator2>
		bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
										InputIterator2 first2, InputIterator2 last2)
		{
			while (first1 != last1)
			{
				if (first2 == last2 || *first2 < *first1) return false;
				else if (*first1 < *first2) return true;
				++first1;
				++first2;
			}
			return (first2 != last2);
		}

	/*
	   Return true if the range [first1, last2) compare
	   lexicographically lest than the range [first2, last2).
	   The comparision is effectued by "comp".
	**
	   first1, last1 the start and the end of the first range.
	   first2, last2 the start and the end of the second range.
	   comp the function that will compare.
		return true if the first range compares lexicographically less
	   than the second, false otherwise.
	*/
	template <class InputIterator1, class InputIterator2, class Compare>
		bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
										InputIterator2 first2, InputIterator2 last2,
										Compare comp)
		{
			while (first1 != last1)
			{
				if (first2 == last2 || comp(*first2, *first1)) return false;
				else if (comp(*first1, *first2)) return true;
				++first1;
				++first2;
			}
			return (first2 != last2);
		}

	template <typename T>
	struct BST_Node
	{
		public :

			/* First template argument, the type of stocked value */
			typedef T   value_type;

			value_type value;
			BST_Node* parent;
			BST_Node* left;
			BST_Node* right;

			/*
			   Default.
			   Create a BST_Node with default initisialized value.
			   Left and right branch pointer to a "u_nullptr" (t_nullptr).
			*/
			BST_Node ()
			:
				value(),
				parent(u_nullptr),
				left(u_nullptr),
				right(u_nullptr)
			{}

			/*
			   Default.
			   Create a BST_Node with default initisialized value.
			   Left and right branch pointer to a "u_nullptr" (t_nullptr).
			*/
			BST_Node (BST_Node* parent = u_nullptr,
					BST_Node* left = u_nullptr, BST_Node* right = u_nullptr)
			:
				value(),
				parent(parent),
				left(left),
				right(right)
			{}

			/*
			   Value.
			   Create a BST_Node with value defined by a copy of "val".
			   Left and right branch pointer to a "u_nullptr" (t_nullptr).
			**
			   val the value to copy.
			*/
			BST_Node (const value_type& val, BST_Node* parent = u_nullptr,
					BST_Node* left = u_nullptr, BST_Node* right = u_nullptr)
			:
				value(val),
				parent(parent),
				left(left),
				right(right)
			{}

			/*
			   Copy.
			   Create a BST_Node that a copy of "nd".
			   The value is initalized by a copy of "nd" value.
			   Left and right branch point to the same than "nb" branches.
			**
			   nd the BST_Node to copy.
			*/
			BST_Node (const BST_Node& nd)
			:
				value(nd.value),
				parent(nd.parent),
				left(nd.left),
				right(nd.right)
			{}

			virtual ~BST_Node() {}

			/*
			   Equal operator.
			   Create a BST_Node that a copy of "nd".
			   The value is initalized by a copy of "nd" value.
			   Left and right branch point to the same than "nb" branches.
			**
			   nd the BST_Node to copy.
				return *this.
			*/
			BST_Node &operator=(const BST_Node& nd)
			{
				if (nd == *this)
					return (*this);

				this->value = nd.value;
				this->parent = nd.parent;
				this->left = nd.left;
				this->right = nd.right;

				return (*this);
			}

			/*
			   Compare two BST_Node to know
			   if they contains the same value.
			**
			   nd the BST_Node to compare.
				return true if the value are the same,
			   otherwise no.
			*/
			bool operator==(const BST_Node& nd)
			{
				if (value == nd.value)
					return (true);
				return (false);
			}
	};

	/* List Node : */
	template <class Data_T>
	struct Doubly_Linked_Node
	{
		public :

			Doubly_Linked_Node  *prev;
			Doubly_Linked_Node  *next;
			Data_T              data;

			/*
			   Default:
			   Create a node with next and prev
			   value that pointing to u_nullptr.
			   data is unitialized.
			*/
			Doubly_Linked_Node()
			:
				prev(u_nullptr),
				next(u_nullptr)
			{}

			/*
			   Data init:
			   Create a node with next and prev
			   value that pointing to u_nullptr.
			   data is itialized to "val".
			**
			   val the data of this node.
			*/
			Doubly_Linked_Node(const Data_T& val)
			:
				prev(u_nullptr),
				next(u_nullptr),
				data(val)
			{}

			/*
			   Init:
			   Create a node with next and prev
			   value that pointing to parameters "prev" & "next".
			   data is itialized to "val".
			**
			   val the data of this node.
			   prev,next the previous and next node.
			*/
			Doubly_Linked_Node(const Data_T& val,
				Doubly_Linked_Node *prev, Doubly_Linked_Node *next)
			:
				prev(prev),
				next(next),
				data(val)
			{}
	};


} /* End of namespace */

# endif
