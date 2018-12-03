/**
 * @file SimHit.hh
 * @author     Piotr Podlaski
 * @brief      Definition of SimHit struct
 */

#ifndef SIMHIT_H
#define SIMHIT_H

/**
 * @brief      Struct holding information about single energy deposit cluster
 */
struct SimHit
{
	double x; ///< X coordinate of the hit
	double y; ///< Y coordinate of the hit
	double z; ///< Z coordinate of the hit
	double Edep; ///< Energy deposit of the hit
};

#endif