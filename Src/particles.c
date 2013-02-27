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
	
	long double velocityX, velocityY, velocityZ;
	long double initialVelocityX, initialVelocityY, initialVelocityZ;
	long double accelerationX, accelerationY, accelerationZ;
	long double forceX, forceY, forceZ;
	long double displacementX, displacementY, displacementZ;

};

struct particle electronAttributes;
struct particle protonAttributes;
							 
void calculate_force( int *types , int index1 , int index2 , struct movement *this);
void calculate_acceleration( struct movement *this, long double mass );
void calculate_velocity( struct movement *this , long double time );
void calculate_displacement( int *types, long double time , struct movement *this);

void init_particle_constants() {
	
	electronAttributes.mass = 9.10938188e-31;
	electronAttributes.charge = -1.60217646e-19;
	
	protonAttributes.mass = 1.67262158e-27;
	protonAttributes.charge = 1.60217646e-19;

}

void *electron( void *loc ) {

	int x = 0;
	
	int *index = (int *)loc;
	struct movement current = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	
	struct timespec *hold = ( struct timespec *)malloc( sizeof(struct timespec) );
	hold[0].tv_sec = 0;
	hold[0].tv_nsec = 250000000;
	
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
	
	}
	
	electronLocations[*index].done = 1;
	
	int types[2];
	
	long double time = 0.100000000000000;
	long double initialTime = time;
	
	// How do forces apply to each other?
	while (finished == 0) {
	
		types[0] = ELECTRON;
		types[1] = ELECTRON;
		
		for (x = 0;x < numParticles[0].amountElectron;x++) {
		
			if (x == *index) {
			
				continue;
			
			} else {
				
				
				calculate_force(types, *index, x , &current);
				calculate_acceleration( &current, electronAttributes.mass );
				calculate_velocity( &current, time - initialTime );					
			
				calculate_displacement( types , time - initialTime , &current );
			
			}
		
		}
		
		types[1] = PROTON;
		for (x = 0;x < numParticles[0].amountProton;x++) {
			
			
				calculate_force( types, *index, x, &current );
				calculate_acceleration( &current, electronAttributes.mass );
				calculate_velocity( &current, time - initialTime );
		
		}
		types[1] = ELECTRON;
		
		electronLocations[*index].x = current.displacementX;
		electronLocations[*index].y = current.displacementY;
		electronLocations[*index].z = current.displacementZ;
		
		printf("\n%d x = %f", *index, electronLocations[*index].x);
		printf("\n%d y = %f", *index, electronLocations[*index].y);
		printf("\n%d z = %f", *index, electronLocations[*index].z);
		
		initialTime = time;
		time += 0.100000000000000;
		nanosleep( hold, NULL );
	
	}
	
	
	pthread_exit(NULL);
	
}

void *proton( void *loc ) {
	
	
	int x = 0;
	
	int *index = (int *)loc;
	
	
	protonLocations[*index].x = (float)rand()/(float)RAND_MAX - (float)rand()/(float)RAND_MAX;
	protonLocations[*index].y = (float)rand()/(float)RAND_MAX - (float)rand()/(float)RAND_MAX;
	protonLocations[*index].z = (float)rand()/(float)RAND_MAX - (float)rand()/(float)RAND_MAX;
	
	protonLocations[*index].done = 1;
	
	for (x = 0;x < numParticles[0].amountElectron;x++) {
		
		if ( protonLocations[*index].x == electronLocations[x].x &&
			 protonLocations[*index].y == electronLocations[x].y && 
			 protonLocations[*index].z == electronLocations[x].z) {
				 
				protonLocations[*index].x = (float)rand()/(float)RAND_MAX - (float)rand()/(float)RAND_MAX;
				protonLocations[*index].y = (float)rand()/(float)RAND_MAX - (float)rand()/(float)RAND_MAX;
				protonLocations[*index].z = (float)rand()/(float)RAND_MAX - (float)rand()/(float)RAND_MAX;
				
				x = 0;
		
		}
		
	}
	
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

	pthread_exit(NULL);
	
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
	

}

void calculate_acceleration( struct movement *this , long double mass ) {
	
	this->accelerationX += acceleration_forceMass( this->forceX , mass );
	this->accelerationY += acceleration_forceMass( this->forceY , mass );
	this->accelerationZ += acceleration_forceMass( this->forceZ , mass );


}
void calculate_velocity( struct movement *this , long double time ) {
	
	this->velocityX += velocity_accelerationTime( this->accelerationX, time );
	this->velocityY += velocity_accelerationTime( this->accelerationY, time );
	this->velocityZ += velocity_accelerationTime( this->accelerationZ, time );
	
}

void calculate_displacement( int *types , long double time , struct movement *this ) {
	
	if ( types[0] == ELECTRON && types[1] == ELECTRON ) {
		
		//metres_velocityTime( this-> );
	
	} else if ( types[0] == ELECTRON && types[1] == PROTON ) {
		
	
	
	}
	
}
