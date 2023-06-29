# mySTL-containers

The goal of the project is to rewrite some container types of the C++ standard template library for better understanding of internal process.
As a bonus task containers SET and MAP are implemented using red-black tree data structure.

### Required implementations
- Must implement following containers and their associated functions:
  - Vector
  - Stack
  - Map
  - Set  
- Compare outputs and timing with original STL containers (you can be up to 20 times slower).
- Member functions, Non-member and overloads are expected.
- Must use std::allocator.
- If the container has an iterator system, must implement it.
- iterators_traits, reverse_iterator, enable_if, is_integral, equal/lexicographical compare, std::pair, std::make_pair, must be reimplemented.
- Forbidden to  implement more public functions than the ones offered in the standard containers. Everything else must be private or protected. Each public function/- variable must be justified.
- For non-member overloads, the keyword friend is allowed. Each use of friend must be justified and will be checked during evaluation.

Launch the program
- Clone the project and access the folder
```
git clone https://github.com/maryana-la/mySTL && cd mySTL
```

- Build project and run test
```
make test
```

Accepted difference is in namespace, exception description and timing:

![output](https://github.com/maryana-la/mySTL/assets/75047240/21e42e3a-917f-421f-a646-8d15ea1a9fef)
