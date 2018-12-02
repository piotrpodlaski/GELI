/*!@mainpage Monte Carlo framework for eliTPC detector
 *
 * @section intro_sec Introduction
 *
 * This software pacakge contains the code for simulations of the eliTPC
 * detector in Geant4 framework GELI - Geant4ELI.
 *
 * @section install_sec Software modules
 * Framework consists of two modules:
 * @subsection geant1_part Geant4
 * This section is responsible for MC simulation of physical processes in
 * proper detecot geometry imported from 3D model. It outputs energy deposit
 * in 3D space which are then fed into electron transport simulator.
 * @subsection transport_part Transport simulator
 * This part of the software performs electron transport simulation of the primary
 * energy deposit. It is capable of simulating the diffusion, electron
 * attachment and gain variatios across the detector amplification stage
 *
 */
