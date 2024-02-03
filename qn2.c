#include <math.h>

#define IMU_DEG(x) ((x) * 180 / M_PI)
#define X 30			//random magic number
#define CHASSIS_LENGTH 40	//random number
#define CHASSIS_WIDTH 30	//random number
#define MOVE_SPEED 50		//random number
#define ROTATE_SPEED 30		//random number

void swerve_turn(uint8_t module_num, float gm6020_ang, int16_t m3508_rpm);

void chassis_control(uint8_t move_deg) {
  int theta = atan(CHASSIS_WIDTH / CHASSIS_LENGTH);
	int module_1_3_angle = 90 – theta;
	int module_2_4_angle = 270 + theta;
  int16_t module1_speed = (IMU_DEG(imu_north) >= (90 – X) && IMU_DEG(imu_north) <= (90 + X)) ? 
                          MOVE_SPEED : 
                          ((IMU_DEG(imu_north) >= (270 – X) && IMU_DEG(imu_north) <= (270 + X)) ? 
                          -MOVE_SPEED : ROTATE_SPEED);
  int16_t module2_speed = ROTATE_SPEED;
  int16_t module3_speed = ROTATE_SPEED;
  int16_t module4_speed = (IMU_DEG(imu_north) <= X || IMU_DEG(imu_north) >= 360 – X) ? 
                          MOVE_SPEED : 
                          ((IMU_DEG(imu_north) >= (180 – X) && IMU_DEG(imu_north) <= (180 + X)) ? 
                          -MOVE_SPEED : ROTATE_SPEED);

  float module1_angle = ((IMU_DEG(imu_north) >= (90 – X) && IMU_DEG(imu_north) <= (90 + X)) || 
                        (IMU_DEG(imu_north) >= (270 – X) && IMU_DEG(imu_north) <= (270 + X))) ? 
                        move_deg: module_1_3_angle;
  float module2_angle = module_2_4_angle;
  float module3_angle = module_1_3_angle;
  float module4_angle = ((IMU_DEG(imu_north) > X && IMU_DEG(imu_north) < (180 – X)) || 
                        (IMU_DEG(imu_north) > (180 + X) && IMU_DEG(imu_north) < (360 – X))) ? 
                        module_2_4_angle : move_deg;
  
  swerve_turn(uint8_t 1, float module1_angle, int16_t module1_speed);
  swerve_turn(uint8_t 2, float module2_angle, int16_t module2_speed);
  swerve_turn(uint8_t 3, float module3_angle, int16_t module3_speed);
  swerve_turn(uint8_t 4, float module4_angle, int16_t module4_speed);
}
