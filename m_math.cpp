#include"m_math.h"

double m_ofNoise(double x, double y, double z) {
	return m_slang_library_noise3(x, y, z)*0.5f + 0.5f;
}
