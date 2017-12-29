# BidirectionalMap
A simple (and naive) implementation of bidirectional map that allows fast access to pairs of values of different types (!) by both values as keys. Although a boost::bimap implementation of such container (http://www.boost.org/doc/libs/1_66_0/libs/bimap/) already exists, it was a challenge to create my own container. Moreover, since this implementation can use std::unordered_map, access to container members can be up to 40 % faster than for boost::bimap (you can run Benchmark project to check).

For initial implementation, I've picked some ideas presented by Vittorio Romeo (https://codereview.stackexchange.com/questions/42427/bidirectional-map-based-on-memory-manipulation). 

Unlike boost::bimap its interface is not STL-like, but made to tailor my needs. First of all, paired items must be of different types (e.g. int-string pairs, but not int-int pairs). There are only few members in the interface, presented in the code sample on the Wiki page.
