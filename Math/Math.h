#pragma once

class Math
{
public:
	static constexpr float PI = 3.14159265359f;
	static constexpr float PI_2 = 6.28318530718f;
	static constexpr float PI_DIV_2 = 1.57079632679f;
	static constexpr float PI_DIV_4 = 0.78539816339f;
	static constexpr float TO_DEG = 180.0f / PI;
	static constexpr float TO_RAD = PI / 180.0f;

public:
	template<typename T>
	static const int Random(const T& min, const T& max);

private:
	static std::random_device rd;
	static std::mt19937 mt;
};

template<typename T>
inline const int Math::Random(const T& min, const T& max)
{
	return std::uniform_int_distribution<T>{min, max}(mt);
}
