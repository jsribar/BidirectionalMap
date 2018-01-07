# BidirectionalMap
A simple (and naive) implementation of bidirectional map that allows fast access to pairs of values of same or different types by both values as keys. Although a boost::bimap implementation of such container (http://www.boost.org/doc/libs/1_66_0/libs/bimap/) already exists, it was a challenge to create my own container. This implementation is not as fast as boost::bimap, but is preatty comparable to it (you can run Benchmark project to check).

For initial implementation, I've picked some ideas presented by Vittorio Romeo (https://codereview.stackexchange.com/questions/42427/bidirectional-map-based-on-memory-manipulation). 

Unlike boost::bimap its interface is not STL-like, but made to tailor my needs. There are only few members in the interface, presented in the code sample on the Wiki page.
