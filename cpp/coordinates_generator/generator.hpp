#ifndef MY__HPP
#define MY__HPP

#include <string>
#include <algorithm>

template<typename T>
struct Coordinates {
	T lat = T(), lng = T();
	Coordinates(T la, T ln):lat(la), lng(ln) {}
	operator std::string() const {
		return std::to_string(lat) + " " + std::to_string(lng);
	}
};

template<typename T>
std::ostream& operator<< (std::ostream& os, const Coordinates<T>& c) {
	return os << c.lat << ' ' << c.lng;
}

template <typename T = double>
auto generate(std::size_t max,
			  double stddev = 1.0,
			  std::size_t mean_lat = 55, std::size_t mean_lng = 37) {

	static std::random_device rd;
	static std::mt19937_64 gen(rd());
	static std::normal_distribution<T> lat(mean_lat, stddev);
	static std::normal_distribution<T> lng(mean_lng, stddev);

	std::vector<Coordinates<T> > v;
	for (size_t i = 0; i < max; i++)
		v.emplace_back(lat(gen), lng(gen));

	return v;
}

#endif // MY__HPP
