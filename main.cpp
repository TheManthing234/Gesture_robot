/*
 * gesture_128_0.0.cpp
 *
 * Created: 30-01-2019 20:44:17
 * Author : Manasvi Sinha
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
//#include <I2C.h>
#include <inttypes.h>
#include <stdlib.h>		/* Include standard library file */
#include <stdio.h>		/* Include standard I/O library file */


void start_I2C(unsigned char);
int startreg_I2C (unsigned char);
void init_I2C (void);
void read_accl (void);
void read_gyro (void);
void stop_I2C (void);

void stop_I2C (void)
{
TWCR = (1<<TWINT)|(1<<TWSTO);
while (!(TWCR & (1<<TWINT)));
}

void start_I2C(unsigned char mpuadd)
{
	TWCR|=(1<<TWINT)|(1<<TWEN)|(1<<TWSTA);
	while (!(TWCR & (1<<TWINT)));
	
	TWDR = mpuadd;
	TWCR = (1<<TWEN)|(1<<TWINT);
	while (!(TWCR & (1<<TWINT)));
}

int startreg_I2C (unsigned char regs)
{
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while (!(TWCR & (1<<TWINT)));
	TWDR=regs;
	return TWDR;
}

void init_I2C()
{
	TWBR=12;
	TWCR=(1<<TWEN);
	TWSR=0x00;
}

int main (void)
{
	start_I2C(0x68);
	while (1)
	{
	read_accl ();
	read_gyro ();
	stop_I2C();
	}
}

void read_accl (void)
{
	float acc_x,acc_y,acc_z;
	acc_x=(((int)startreg_I2C (0x3B)<<8)|((int)startreg_I2C (0x3C)))/16384.0;
	acc_y=(((int)startreg_I2C (0x3D)<<8)|((int)startreg_I2C (0x3E)))/16384.0;
	acc_z=(((int)startreg_I2C (0x3F)<<8)|((int)startreg_I2C (0x40)))/16384.0;
}

void read_gyro (void)
{
	
	float gyro_x,gyro_y,gyro_z;
	gyro_x=(((int)startreg_I2C (0x43)<<8)|((int)startreg_I2C (0x44)))/16.4;
	gyro_y=(((int)startreg_I2C (0x45)<<8)|((int)startreg_I2C (0x46)))/16.4;
	gyro_z=(((int)startreg_I2C (0x47)<<8)|((int)startreg_I2C (0x48)))/16.4;
}
