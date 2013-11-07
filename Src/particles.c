/*
 * particles.c
 * 
 * Copyright 2013 Michael Davenport <mike3214545@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include "particles.h"

#define ELECTRON 0
#define PROTON 1
#define NEUTRON 2

#define EL_EL 0
#define EL_PR 1
#define PR_PR 2
#define PR_EL 3

struct particle {
	
	long double mass, charge;
	
};


/*
 * 
 * int type allows certain portions of the code to know what the particle
 * is interacting with.
 * 
 * Interactions
 * 
 * 0 - Electron/Electron
 * 1 - Electron/Proton
 * 2 - Proton/Proton
 * 3 - Proton/Electron
 * 
 * */
struct movement {
	
	int type;
	
	long double velocity , velocityX , velocityY , velocityZ;
	long double initialVelocityX , initialVelocityY , initialVelocityZ;
	long double acceleration , accelerationX , accelerationY , accelerationZ;
	long double force , forceX , forceY , forceZ;
	long double displacementX , displacementY , displacementZ;

};



struct particle electronAttributes;
struct particle protonAttributes;

float get_float();

void check_system();

void calculate_difference( int index1 , int index2 , long double *x , long double *y , long double *z , int type );
							 
void calculate_force( int index1 , int index2 , struct movement *this );
void calculate_acceleration( long double mass , struct movement *this );
void calculate_velocity( int index1, int index2 , long double time , struct movement *this );
void calculate_displacement( int index1 , int index2 , long double time , struct movement *this);
void calculate_components( long double x , long double y , long double z , struct movement *this , int type );

void init_particle_constants() {
	
	electronAttributes.mass = 9.10938188e-31;
	electronAttributes.charge = -1.60217646e-19;
	
	protonAttributes.mass = 1.67262158e-27;
	protonAttributes.charge = 1.60217646e-19;

}

void *electron( void *loc ) {

	int x = 0;
	
	int *index = (int *)loc;
	struct movement current = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	
	struct timespec *hold = ( struct timespec *)malloc( sizeof( struct timespec ) );
	hold[0].tv_sec = 0;
	hold[0].tv_nsec = 250000000;
	
	electronLocations[*index].x = get_float() - get_float();
	electronLocations[*index].y = get_float() - get_float();
	electronLocations[*index].z = get_float() - get_float();
	
	//Justs checks to see if no electron is holding the same position.
	//The new location is based on probability that it won't be there again.
	for ( x = 0;x < *index; x++) {
			
		if ( electronLocations[*index].x == electronLocations[x].x && 
			 electronLocations[*index].y == electronLocations[x].y &&
			 electronLocations[*index].z == electronLocations[x].z ) {
					
			electronLocations[*index].x = get_float() - get_float();
			electronLocations[*index].y = get_float() - get_float();
			electronLocations[*index].z = get_float() - get_float();
				
			x = 0;
				
		}
		
	}
	
	electronLocations[*index].done = 1;
	check_system();
	
	//Math can only be done two numbers at a time.
	
	long double time = get_system_time();
	long double initialTime = time;
	
	/*
	 * 
	 * This extensive while loop allows for particle interactions.
	 * 
	 * It compares the position values of other memory locations in in the multiple array's
	 * 
	 * */
	while ( systemFinished == 0 ) {
	
		current.type = 0;
		
		for ( x = 0;x < numParticles[0].amountElectron;x++ ) {
		
			if ( x == *index ) {
				
				continue;
			
			} else {
				
				calculate_force( *index, x , &current );
				calculate_acceleration( electronAttributes.mass , &current );
				calculate_velocity( *index , x ,  time - initialTime , &current );					
				calculate_displacement( *index , x , time - initialTime , &current );
			
			}
		
		}
		
		current.type = 1;
		
		for ( x = 0;x < numParticles[0].amountProton;x++ ) {
			
			
			calculate_force( *index, x, &current );
			calculate_acceleration( electronAttributes.mass , &current );
			calculate_velocity( *index, x , time - initialTime , &current );
			calculate_displacement( *index , x , time - initialTime , &current );
		
		}
		
		electronLocations[*index].x += current.displacementX;
		electronLocations[*index].y += current.displacementY;
		electronLocations[*index].z += current.displacementZ;
		
		initialTime = time;
		time += get_system_time();
		nanosleep( hold, NULL );
	
	}
	
	
	pthread_exit(EXIT_SUCCESS);
	
}

void *proton( void *loc ) {
	
	
	int x = 0;
	
	int *index = (int *)loc;
	
	struct movement current = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	struct timespec *hold = ( struct timespec *)malloc( sizeof( struct timespec ) );
	hold[0].tv_sec = 0;
	hold[0].tv_nsec = 250000000;
	
	
	protonLocations[*index].x = get_float() - get_float();
	protonLocations[*index].y = get_float() - get_float();
	protonLocations[*index].z = get_float() - get_float();
	
	for ( x = 0;x < numParticles[0].amountElectron;x++ ) {
		
		if ( protonLocations[*index].x == electronLocations[x].x &&
			 protonLocations[*index].y == electronLocations[x].y && 
			 protonLocations[*index].z == electronLocations[x].z) {
				 
				protonLocations[*index].x = get_float() - get_float();
				protonLocations[*index].y = get_float() - get_float();
				protonLocations[*index].z = get_float() - get_float();
				
				x = 0;
		
		}
		
	}
		
	for ( x = 0; x < *index;x++ ) {
			
		if ( protonLocations[*index].x == protonLocations[x].x &&
			 protonLocations[*index].y == protonLocations[x].y &&
			 protonLocations[*index].z == protonLocations[x].z) {
					 
				protonLocations[*index].x = get_float() - get_float();
				protonLocations[*index].y = get_float() - get_float();
				protonLocations[*index].z = get_float() - get_float();
					
				x = 0;
				 
		}
			
	}
	
	protonLocations[*index].done = 1;
	check_system();
	
	
	long double time = get_system_time(); 
	long double initialTime = time;
	
	while ( systemFinished == 0 ) {
		
		current.type = 3;
		
		for ( x = 0;x < numParticles[0].amountElectron;x++ ) {
			
			calculate_force( *index , x , &current );
			calculate_acceleration( protonAttributes.mass , &current );
			calculate_velocity( *index , x , time - initialTime , &current );
			calculate_displacement( *index , x , time - initialTime , &current );
			
		
		}
		current.type = 2;
		
		for ( x = 0;x < numParticles[0].amountProton;x++ ) {
			
			if ( x == *index ) {
				
				continue;
			
			} else {
			
				calculate_force( *index , x , &current );
				calculate_acceleration( protonAttributes.mass , &current );
				calculate_velocity( *index , x , time - initialTime , &current );
				calculate_displacement( *index , x , time - initialTime , &current );
				
			}
			
		}
		
		protonLocations[*index].x += current.displacementX;
		protonLocations[*index].y += current.displacementY;
		protonLocations[*index].z += current.displacementZ;
		
		initialTime = time;
		time += get_system_time();
		nanosleep( hold , NULL );
	
	}

	pthread_exit(EXIT_SUCCESS);
	
}

float get_float() {
	
	return ( float )rand()/( float )RAND_MAX;

}

void check_system() {
	
	int x;
	
	//checks to see if the system is ready. If done == 0, particle is not ready.
	for ( x = 0; x < numParticles[0].amountElectron;x++ ) {
			
		if ( electronLocations[x].done == 0 ) {
				
			x--;
			
		}
		
	}
	for ( x = 0;x < numParticles[0].amountProton; x++ ) {
		
		if ( protonLocations[x].done == 0 ) {
		
			x--;
			
		}
	
	}
	
}

void calculate_difference( int index1 , int index2 , long double *x , long double *y , long double *z , int type ) {
	
	switch ( type ) {
		
		case EL_EL:
		
			*x = electronLocations[index1].x - electronLocations[index2].x;
			*y = electronLocations[index1].y - electronLocations[index2].y;
			*z = electronLocations[index1].z - electronLocations[index2].z;
			
		break;
		
		case EL_PR:
		
			*x = electronLocations[index1].x - protonLocations[index2].x;
			*y = electronLocations[index1].y - protonLocations[index2].y;
			*z = electronLocations[index1].z - protonLocations[index2].z;
		
		break;
		
		case PR_PR:
		
			*x = protonLocations[index1].x - protonLocations[index2].x;
			*y = protonLocations[index1].y - protonLocations[index2].y;
			*z = protonLocations[index1].z - protonLocations[index2].z;
		
		break;
		
		case PR_EL:
		
			*x = protonLocations[index1].x - electronLocations[index2].x;
			*y = protonLocations[index1].y - electronLocations[index2].y;
			*z = protonLocations[index1].z - electronLocations[index2].z;
		
		break;
	
	
	}

}

void calculate_force( int index1 , int index2 ,  struct movement *this ) {
	
	
	//Because interaction at the nano level is too quickly to see.
	long double scale = 50;
	
	long double x , y , z;
	long double distance;
	
	
	calculate_difference( index1 , index2 , &x , &y , &z , this->type );
		
	distance = sqrtl( ( x * x ) + ( y * y ) + ( z * z ) );
	
	switch ( this->type ) {
		
		case EL_EL:
		
			this->force += force_kqqR2( electronAttributes.charge , electronAttributes.charge ,
										distance * scale ) - this->force;
										
		break;
		
		case EL_PR:
		
			this->force += force_kqqR2( electronAttributes.charge , protonAttributes.charge ,
										distance * scale ) - this->force;
		
		break;
		
		case PR_PR:
		
			this->force += force_kqqR2( protonAttributes.charge , protonAttributes.charge ,
									distance * scale ) - this->force;
		
		break;
		
		case PR_EL:
			
			this->force += force_kqqR2( protonAttributes.charge , electronAttributes.charge , 
										distance * scale ) - this->force;
		
		break;
	
	
	}

}

void calculate_acceleration( long double mass , struct movement *this ) {
	
	this->acceleration += acceleration_forceMass( this->force , mass ) - this->acceleration;

}
void calculate_velocity( int index1 , int index2 ,  long double time , struct movement *this ) {
	
	long double x , y , z;
	
	calculate_difference( index1 , index2 , &x , &y , &z , this->type );
	
	this->velocity += velocity_accelerationTime( this->acceleration, time ) - this->velocity;
	
	calculate_components( x , y , z , this , 2);
	
}

void calculate_displacement( int index1 , int index2 , long double time , struct movement *this ) {
	
	long double scale = 20;
	
	
	switch ( this->type ) {
		
		case EL_EL:
		
			if ( electronLocations[index1].x > electronLocations[index2].x && electronLocations[index1].x < 1.0) {
			
				this->displacementX += ( metres_velocityTime( this->velocityX , time ) / scale );
		
			} else if ( electronLocations[index1].x == electronLocations[index2].x ) {
			
			
		
			} else {
			
				this->displacementX -=  ( metres_velocityTime( this->velocityX , time ) / scale );
		
			}
		
			if ( electronLocations[index1].y > electronLocations[index2].y && electronLocations[index1].y < 1.0 ) {
			
				this->displacementY += ( metres_velocityTime( this->velocityY , time ) / scale );
		
			} else if ( electronLocations[index1].y == electronLocations[index2].y ) {
			
				
		
			} else {
			
				this->displacementY -= ( metres_velocityTime( this->velocityY , time ) / scale );
				
			}
		
			if (electronLocations[index1].z > electronLocations[index2].z && electronLocations[index1].z < 1.0 ) {
			
				this->displacementZ += ( metres_velocityTime( this->velocityZ , time ) / scale );
		
			} else if ( electronLocations[index1].z == electronLocations[index2].z ) {
			
			
		
			} else {
			
				this->displacementZ -= ( metres_velocityTime( this->velocityZ , time ) / scale );
			
			}
			
		break;
		
		case EL_PR:
		
			if ( electronLocations[index1].x > protonLocations[index2].x && electronLocations[index1].x > -1.0 ) {
				
				this->displacementX += ( metres_velocityTime( this->velocityX , time ) );
			
			} else if ( electronLocations[index1].x == protonLocations[index2].x ) {
				
				
				
			} else {
				
				this->displacementX -= ( metres_velocityTime( this->velocityX , time ) );
			
			}
			
			if ( electronLocations[index1].y > protonLocations[index2].y && electronLocations[index1].y > -1.0 ) {
				
				this->displacementY += ( metres_velocityTime( this->velocityY , time ) );
			
			} else if ( electronLocations[index1].y == protonLocations[index2].y ) {
				
			
				
			} else {
				
				this->displacementY -= ( metres_velocityTime( this->velocityY , time ) );
			
			}
			
			if ( electronLocations[index1].z > protonLocations[index2].z && electronLocations[index1].z > -1.0 ) {
				
				this->displacementZ += ( metres_velocityTime( this->velocityZ , time ) );
			
			} else if ( electronLocations[index1].z == protonLocations[index2].z ) {
				
				
			
			} else {
				
				this->displacementZ -= ( metres_velocityTime( this->velocityZ , time ) );
			
			}
		
		break;
		
		case PR_PR:
		
			if ( protonLocations[index1].x > protonLocations[index2].x && protonLocations[index1].x < 1.0 ) {
			
				this->displacementX += ( metres_velocityTime( this->velocityX , time ) / scale );
		
			} else if ( protonLocations[index1].x == protonLocations[index2].x ) {
			
			
		
			} else {
			
				this->displacementX -=  ( metres_velocityTime( this->velocityX , time ) / scale );
		
			}
		
			if ( protonLocations[index1].y > protonLocations[index2].y && protonLocations[index1].y < 1.0 ) {
			
				this->displacementY += ( metres_velocityTime( this->velocityY , time ) / scale );
		
			} else if ( protonLocations[index1].y == protonLocations[index2].y ) {
			
				
		
			} else {
			
				this->displacementY -= ( metres_velocityTime( this->velocityY , time ) / scale );
				
			}
		
			if ( protonLocations[index1].z > protonLocations[index2].z && protonLocations[index1].z < 1.0 ) {
			
				this->displacementZ += ( metres_velocityTime( this->velocityZ , time ) / scale );
		
			} else if ( protonLocations[index1].z == protonLocations[index2].z ) {
			
			
		
			} else {
			
				this->displacementZ -= ( metres_velocityTime( this->velocityZ , time ) / scale );
			
			}
		
		break;
		
		case PR_EL:
		
			if ( protonLocations[index1].x > electronLocations[index2].x && protonLocations[index1].x > -1.0 ) {
				
				this->displacementX += ( metres_velocityTime( this->velocityX , time ) );
			
			} else if ( protonLocations[index1].x == electronLocations[index2].x ) {
				
				
				
			} else {
				
				this->displacementX -= ( metres_velocityTime( this->velocityX , time ) );
			
			}
			
			if ( protonLocations[index1].y > electronLocations[index2].y && protonLocations[index1].y > -1.0 ) {
				
				this->displacementY += ( metres_velocityTime( this->velocityY , time ) );
			
			} else if ( protonLocations[index1].y == electronLocations[index2].y ) {
				
			
				
			} else {
				
				this->displacementY -= ( metres_velocityTime( this->velocityY , time ) );
			
			}
			
			if ( protonLocations[index1].z > electronLocations[index2].z && protonLocations[index1].z > -1.0 ) {
				
				this->displacementZ += ( metres_velocityTime( this->velocityZ , time ) );
			
			} else if ( protonLocations[index1].z == electronLocations[index2].z ) {
				
				
			
			} else {
				
				this->displacementZ -= ( metres_velocityTime( this->velocityZ , time ) );
			
			}
		
		break;
		
	}
	
}
void calculate_components( long double x , long double y , long double z , struct movement *this , int type ) {
	
	long double xytheta = atan( y / x ), yztheta = atan( z / y );
	
	switch ( type ) {
		
		case 0: 
		
			this->forceX += ( this->force * cos( xytheta ) );
			this->forceY += ( this->force * sin( xytheta ) );
			this->forceZ += ( this->force * sin( yztheta ) );
			 
		break;
		
		case 1:
		
			this->accelerationX += ( this->acceleration * cos( xytheta ) );
			this->accelerationY += ( this->acceleration * sin( xytheta ) );
			this->accelerationZ += ( this->acceleration * sin( yztheta ) );
		
		break;
		
		case 2:
		
			this->velocityX += ( this->velocity * cos( xytheta ) );
			this->velocityY += ( this->velocity * sin( xytheta ) );
			this->velocityZ += ( this->velocity * sin( yztheta ) );
		
		break;
	
	
	} 


}
