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

struct particle {
	
	long double mass, charge;
	
};
struct movement {
	
<<<<<<< HEAD
	long double velocityX, velocityY, velocityZ;
	long double initialVelocityX, initialVelocityY, initialVelocityZ;
	long double accelerationX, accelerationY, accelerationZ;
	long double forceX, forceY, forceZ;
	long double displacementX, displacementY, displacementZ;
=======
	long double velocity , velocityX , velocityY , velocityZ;
	long double initialVelocityX , initialVelocityY , initialVelocityZ;
	long double acceleration , accelerationX , accelerationY , accelerationZ;
	long double force , forceX , forceY , forceZ;
	long double displacementX , displacementY , displacementZ;
>>>>>>>    testing

};

struct particle electronAttributes;
struct particle protonAttributes;

<<<<<<< HEAD
void calculate_displacement( int *types, long double time , struct movement *this);
							 
void calculate_velocity( struct movement *cords );
void calculate_force( int *types , int index1 , int index2 , struct movement *this);
=======
float get_float();
							 
void calculate_force( int *types , int index1 , int index2 , struct movement *this);
void calculate_acceleration( struct movement *this, long double mass );
void calculate_velocity( struct movement *this , long double time );




void calculate_displacement( int *types, int index1 , int index2 , long double time , struct movement *this);
>>>>>>> testing

void init_particle_constants() {
	
	electronAttributes.mass = 9.10938188e-31;
<<<<<<< HEAD
	//printf("%.39Lf", electronAttributes.mass);
=======
>>>>>>> testing
	electronAttributes.charge = -1.60217646e-19;
	
	protonAttributes.mass = 1.67262158e-27;
	protonAttributes.charge = 1.60217646e-19;

}

void *electron( void *loc ) {

	int x = 0;
	
	int *index = (int *)loc;
<<<<<<< HEAD
	struct movement current = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
=======
	struct movement current = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
>>>>>>> testing
	
	struct timespec *hold = ( struct timespec *)malloc( sizeof(struct timespec) );
	hold[0].tv_sec = 0;
	hold[0].tv_nsec = 250000000;
	
<<<<<<< HEAD
	electronLocations[*index].x = (float)rand()/(float)RAND_MAX - (float)rand()/(float)RAND_MAX;
	electronLocations[*index].y = (float)rand()/(float)RAND_MAX - (float)rand()/(float)RAND_MAX;
	electronLocations[*index].z = (float)rand()/(float)RAND_MAX - (float)rand()/(float)RAND_MAX;
	
	//Justs checks to see if no electron is holding the same position.
	//The new location is based on probability that it won't be there again.
	if (  *index != 0 ) {
		
		for ( x = 0;x < *index; x++) {
			
			if (electronLocations[*index].x == electronLocations[x].x && 
			electronLocations[*index].y == electronLocations[x].y &&
			electronLocations[*index].z == electronLocations[x].z) {
					
				electronLocations[*index].x = (float)rand()/(float)RAND_MAX - (float)rand()/(float)RAND_MAX;
				electronLocations[*index].y = (float)rand()/(float)RAND_MAX - (float)rand()/(float)RAND_MAX;
				electronLocations[*index].z = (float)rand()/(float)RAND_MAX - (float)rand()/(float)RAND_MAX;
				
				x = 0;
				
			}
		
		}
	
=======
	electronLocations[*index].x = .5000000; //get_float() - get_float();
	electronLocations[*index].y = .5000000; //get_float() - get_float();
	electronLocations[*index].z = .5000000; //get_float() - get_float();
	
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
		
>>>>>>> testing
	}
	
	electronLocations[*index].done = 1;
	
<<<<<<< HEAD
=======
	
	//Math can only be done two numbers at a time.
>>>>>>> testing
	int types[2];
	
	long double time = 0.100000000000000;
	long double initialTime = time;
<<<<<<< HEAD
	
	// How do forces apply to each other?
	while (finished == 0) {
	
		types[0] = ELECTRON;
		types[1] = PROTON;
		
		for (x = 0;x < numParticles[0].amountElectron;x++) {
		
			if (x == *index) {
=======
		
	
	//checks to see if the system is ready.
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
	
	// How do forces apply to each other?
	while ( finished == 0 ) {
	
		types[0] = ELECTRON;
		types[1] = ELECTRON;
		
		for ( x = 0;x < numParticles[0].amountElectron;x++ ) {
		
			if ( x == *index ) {
>>>>>>> testing
			
				continue;
			
			} else {
				
				
<<<<<<< HEAD
				calculate_force(types, *index, x , &current);
									
				current.accelerationX += acceleration_forceMass( current.forceX, electronAttributes.mass ) - current.accelerationX;
				current.accelerationY += acceleration_forceMass( current.forceY, electronAttributes.mass ) - current.accelerationY;
				current.accelerationZ += acceleration_forceMass( current.forceZ, electronAttributes.mass ) - current.accelerationZ;
				
				current.velocityX += velocity_accelerationTime( current.accelerationX , time - initialTime ) - current.velocityX;
				current.velocityY += velocity_accelerationTime( current.accelerationY , time - initialTime ) - current.velocityY;
				current.velocityZ += velocity_accelerationTime( current.accelerationZ , time - initialTime ) - current.velocityZ;
			
				calculate_displacement( types , time - initialTime , &current );
			
			}
			
=======
				calculate_force( types , *index, x , &current );
				
				printf("\n%.40Lf Newtons", current.force);
				
				calculate_acceleration( &current, electronAttributes.mass );
				calculate_velocity( &current, time - initialTime );					
				calculate_displacement( types , *index , x , time - initialTime , &current );
			
			}
>>>>>>> testing
		
		}
		
		types[1] = PROTON;
<<<<<<< HEAD
		for (x = 0;x < numParticles[0].amountProton;x++) {
			
			
				calculate_force( types, *index, x, &current );
									
				current.accelerationX += acceleration_forceMass( current.forceX, electronAttributes.mass ) - current.accelerationX;
				current.accelerationY += acceleration_forceMass( current.forceY, electronAttributes.mass ) - current.accelerationY;
				current.accelerationZ += acceleration_forceMass( current.forceZ, electronAttributes.mass ) - current.accelerationZ;
				
				current.velocityX += velocity_accelerationTime( current.accelerationX , time - initialTime ) - current.velocityX;
				current.velocityY += velocity_accelerationTime( current.accelerationY , time - initialTime ) - current.velocityY;
				current.velocityZ += velocity_accelerationTime( current.accelerationZ , time - initialTime ) - current.velocityZ;
				
				//displacementX += -metres_velocityTime( current.velocityX, time - initialTime );
				//displacementY += -metres_velocityTime( current.velocityY, time - initialTime );
				//displacementZ += -metres_velocityTime( current.velocityZ, time - initialTime );
				
		
		}
		
		electronLocations[*index].x = current.displacementX;
		electronLocations[*index].y = current.displacementY;
		electronLocations[*index].z = current.displacementZ;
		
		printf("\n%d x = %f", *index, electronLocations[*index].x);
		printf("\n%d y = %f", *index, electronLocations[*index].y);
		printf("\n%d z = %f", *index, electronLocations[*index].z);
=======
		
		for ( x = 0;x < numParticles[0].amountProton;x++ ) {
			
			
			calculate_force( types, *index, x, &current );
			
			printf("\n%.40Lf Newtons", current.force);
			
			calculate_acceleration( &current, electronAttributes.mass );
			calculate_velocity( &current, time - initialTime );
		
		}
		
		types[1] = ELECTRON;
		
		electronLocations[*index].x += current.displacementX;
		electronLocations[*index].y += current.displacementY;
		electronLocations[*index].z += current.displacementZ;
		
		/*printf("\n%d x = %f", *index, electronLocations[*index].x);
		printf("\n%d y = %f", *index, electronLocations[*index].y);
		printf("\n%d z = %f", *index, electronLocations[*index].z);*/
>>>>>>> testing
		
		initialTime = time;
		time += 0.100000000000000;
		nanosleep( hold, NULL );
	
	}
	
	
	pthread_exit(NULL);
	
}

void *proton( void *loc ) {
	
	
	int x = 0;
	
	int *index = (int *)loc;
	
<<<<<<< HEAD
	
	protonLocations[*index].x = (float)rand()/(float)RAND_MAX - (float)rand()/(float)RAND_MAX;
	protonLocations[*index].y = (float)rand()/(float)RAND_MAX - (float)rand()/(float)RAND_MAX;
	protonLocations[*index].z = (float)rand()/(float)RAND_MAX - (float)rand()/(float)RAND_MAX;
	
	protonLocations[*index].done = 1;
	
	for (x = 0;x < numParticles[0].amountElectron;x++) {
=======
	struct movement current = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	struct timespec *hold = ( struct timespec *)malloc( sizeof(struct timespec) );
	hold[0].tv_sec = 0;
	hold[0].tv_nsec = 250000000;
	
	
	protonLocations[*index].x = -.6700000; //get_float() - get_float();
	protonLocations[*index].y = .6700000; //get_float() - get_float();
	protonLocations[*index].z = .5000000; //get_float() - get_float();
	
	protonLocations[*index].done = 1;
	
	for ( x = 0;x < numParticles[0].amountElectron;x++ ) {
>>>>>>> testing
		
		if ( protonLocations[*index].x == electronLocations[x].x &&
			 protonLocations[*index].y == electronLocations[x].y && 
			 protonLocations[*index].z == electronLocations[x].z) {
				 
<<<<<<< HEAD
				protonLocations[*index].x = (float)rand()/(float)RAND_MAX - (float)rand()/(float)RAND_MAX;
				protonLocations[*index].y = (float)rand()/(float)RAND_MAX - (float)rand()/(float)RAND_MAX;
				protonLocations[*index].z = (float)rand()/(float)RAND_MAX - (float)rand()/(float)RAND_MAX;
=======
				protonLocations[*index].x = get_float() - get_float();
				protonLocations[*index].y = get_float() - get_float();
				protonLocations[*index].z = get_float() - get_float();
>>>>>>> testing
				
				x = 0;
		
		}
		
	}
<<<<<<< HEAD
	
	if ( *index != 0 ) {
		
		for (x = 0; x < *index;x++) {
			
			if ( protonLocations[*index].x == protonLocations[x].x &&
				 protonLocations[*index].y == protonLocations[x].y &&
				 protonLocations[*index].z == protonLocations[x].z) {
					 
					protonLocations[*index].x = (float)rand()/(float)RAND_MAX - (float)rand()/(float)RAND_MAX;
					protonLocations[*index].y = (float)rand()/(float)RAND_MAX - (float)rand()/(float)RAND_MAX;
					protonLocations[*index].z = (float)rand()/(float)RAND_MAX - (float)rand()/(float)RAND_MAX;
					
					x = 0;
					 
			}
			
		}
		
	}
	
	/*while (finished == 0) {
		
		
	
	}*/
=======
		
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
	
	int types[2];
	types[0] = ELECTRON;
	types[1] = PROTON;
	
	while (finished == 0) {
		
		for ( x = 0;x < numParticles[0].amountElectron;x++ ) {
			
			calculate_force( types , *index , x , &current );
			calculate_acceleration( &current , protonAttributes.mass );
			calculate_velocity( &current , .1 );
			
		
		}
		types[1] = PROTON;
		for ( x = 0;x < numParticles[0].amountProton;x++ ) {
			
			calculate_force( types , *index , x , &current );
			calculate_acceleration( &current , protonAttributes.mass );
			calculate_velocity( &current , .1 );
			
		
		}
		types[1] = ELECTRON;
		
		nanosleep( hold , NULL );
	
	}
>>>>>>> testing

	pthread_exit(NULL);
	
}

<<<<<<< HEAD
void calculate_displacement( int *types , long double time , struct movement *this ) {
	
	if ( types[0] == ELECTRON && types[1] == ELECTRON ) {
		
		//metres_velocityTime( this-> );
	
	} else if ( types[0] == ELECTRON && types[1] == PROTON ) {
		
	
	
	}
	
}
void calculate_force( int *types , int index1 , int index2 ,  struct movement *this ) {
	
	
	long double scale = 25;
	
	
	// I realize you cannot determine a particle's attributes just solely on charge. I'll change it later.
	if (types[0] == ELECTRON && types[1] == ELECTRON) {
		
		
		this->forceX += force_kqqR2( electronAttributes.charge , electronAttributes.charge , 
									(electronLocations[index1].x - electronLocations[index2].x) * scale ) - this->forceX;
									 
		this->forceY += force_kqqR2( electronAttributes.charge , electronAttributes.charge ,
									(electronLocations[index1].y - electronLocations[index2].y) * scale ) - this->forceY;
									
		this->forceZ += force_kqqR2( electronAttributes.charge, electronAttributes.charge ,
									(electronLocations[index1].z - electronLocations[index2].z) * scale ) - this->forceZ;
	
	} else if (types[0] == ELECTRON && types[1] == PROTON) {
		
		this->forceX += force_kqqR2( electronAttributes.charge , protonAttributes.charge , 
									(electronLocations[index1].x - protonLocations[index2].x) * scale ) - this->forceX;
									 
		this->forceY += force_kqqR2( electronAttributes.charge , protonAttributes.charge ,
									(electronLocations[index1].y - protonLocations[index2].y) * scale ) - this->forceY;
									
		this->forceZ += force_kqqR2( electronAttributes.charge, protonAttributes.charge ,
									(electronLocations[index1].z - protonLocations[index2].z) * scale ) - this->forceZ;
	
	}
	

=======
float get_float() {
	
	return (float)rand()/(float)RAND_MAX;

}

void calculate_force( int *types , int index1 , int index2 ,  struct movement *this ) {
	
	
	//Because interaction at the nano level is too quickly to see.
	long double scale = 25;
	
	long double x , y , z;
	long double distance;
	
	
	if ( types[0] == ELECTRON && types[1] == ELECTRON ) {
		
		x = electronLocations[index1].x - electronLocations[index2].x;
		y = electronLocations[index1].y - electronLocations[index2].y;
		z = electronLocations[index1].z - electronLocations[index2].z;
		
		distance = sqrtl( ( x * x ) + ( y * y ) + ( z * z ) );
		
		printf("\n%.40Lf metres", distance);
		
		this->force = force_kqqR2( electronAttributes.charge , protonAttributes.charge ,
									distance * scale);
	
	} else if ( types[0] == ELECTRON && types[1] == PROTON ) {
		
		x = electronLocations[index1].x - protonLocations[index2].x;
		y = electronLocations[index1].y - protonLocations[index2].y;
		z = electronLocations[index1].z - protonLocations[index2].z;
		
		distance = sqrtl( ( x * x ) + ( y * y ) + ( z * z ) );
		
		this->force = force_kqqR2( electronAttributes.charge , protonAttributes.charge ,
									distance * scale);
	
	} else if ( types[0] == PROTON && types[1] == PROTON ) {
		
		x = protonLocations[index1].x - protonLocations[index2].x;
		y = protonLocations[index1].y - protonLocations[index2].y;
		z = protonLocations[index1].z - protonLocations[index2].z;
		
		distance = sqrtl( ( x * x ) + ( y * y ) + ( z * z ) );
		
		this->force = force_kqqR2( protonAttributes.charge , protonAttributes.charge ,
									distance * scale);
	
	}
	

}

void calculate_acceleration( struct movement *this , long double mass ) {
	
	this->acceleration += acceleration_forceMass( this->force , mass );


}
void calculate_velocity( struct movement *this , long double time ) {
	
	this->velocity += velocity_accelerationTime( this->acceleration, time );
	
}

void calculate_displacement( int *types , int index1 , int index2 , long double time , struct movement *this ) {
	
	if ( types[0] == ELECTRON && types[1] == ELECTRON ) {
		
		if ( electronLocations[index1].x > electronLocations[index2].x ) {
			
			this->displacementX += metres_velocityTime( this->velocityX, time );
		
		}
		if ( electronLocations[index1].y > electronLocations[index2].x ) {
			
			this->displacementX += metres_velocityTime( this->velocityX, time );
		
		}
		if (electronLocations[index1].z > electronLocations[index2].z ) {
			
			this->displacementX += metres_velocityTime( this->velocityX, time );
		
		}
		
	
	} else if ( types[0] == ELECTRON && types[1] == PROTON ) {
		
		
	
	}
	
>>>>>>> testing
}
