#include "math.h"

struct vector3f zero_acce = {-4089.385,5226.89,7490.706666666667};
uint8_t last_update_a=0;

void get_estimated_error_acce(union quaternion q, struct vector3f *ris) {
	struct raw_accelerometer tmpA;
	uint8_t update = get_raw_accelerometer(&tmpA);
	//to float
	struct vector3f tmp;
	tmp.x = tmpA.x - zero_acce.x;
	tmp.y = tmpA.y - zero_acce.y;
	tmp.z = tmpA.z - zero_acce.z;
	update -= last_update_a; //now in update there is the diff
	if ( update && (tmp.x != 0.0f || tmp.y != 0.0f || tmp.z != 0.0f)) {
		last_update_a += update; //now last_update_a is equal to update prior the diff

		float halfvx, halfvy, halfvz;

		// Normalise accelerometer measurement
		float recipNorm = invSqrt(tmp.x * tmp.x + tmp.y * tmp.y + tmp.z * tmp.z);
		tmp.x *= recipNorm;
		tmp.y *= recipNorm;
		tmp.z *= recipNorm;

		// Estimated direction of gravity
		halfvx = q.q[1] * q.q[3] - q.q[0] * q.q[2];
		halfvy = q.q[0] * q.q[1] + q.q[2] * q.q[3];
		halfvz = q.q[0] * q.q[0] - 0.5f + q.q[3] * q.q[3];

		// Error is sum of cross product between estimated direction and measured direction of field vectors
		ris->x += (tmp.y * halfvz - tmp.z * halfvy);
		ris->y += (tmp.z * halfvx - tmp.x * halfvz);
		ris->z += (tmp.x * halfvy - tmp.y * halfvx);

		//System.out.println("HalfV|"+"halfvx: "+halfvx+" halfvy: "+halfvy+" halfvz: "+halfvz);
		//System.out.println("Halferr|"+"halfex: "+halfex+" halfey: "+halfey+" halfez: "+halfez);
	}
}
