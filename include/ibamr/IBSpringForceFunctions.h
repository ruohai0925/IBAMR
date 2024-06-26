// ---------------------------------------------------------------------
//
// Copyright (c) 2014 - 2023 by the IBAMR developers
// All rights reserved.
//
// This file is part of IBAMR.
//
// IBAMR is free software and is distributed under the 3-clause BSD
// license. The full text of the license can be found in the file
// COPYRIGHT at the top level directory of IBAMR.
//
// ---------------------------------------------------------------------

/////////////////////////////// INCLUDE GUARD ////////////////////////////////

#ifndef included_IBAMR_IBSpringForceFunctions
#define included_IBAMR_IBSpringForceFunctions

/////////////////////////////// INCLUDES /////////////////////////////////////

#include <ibamr/config.h>

/////////////////////////////// CLASS DEFINITION /////////////////////////////

namespace IBAMR
{
/*!
 * \brief Typedef specifying the spring force function API.
 *
 * \return               The (undirected) "tension" force generated by the spring.
 * \param R              The displacement between the "master" and "slave" nodes associated
 *with the
 *spring.
 * \param params         Constitutive parameters.
 * \param rst            The resting length of the spring.
 * \param lag_mastr_idx  The Lagrangian index of the "master" node associated with the spring.
 * \param lag_slave_idx  The Lagrangian index of the "slave" node associated with the spring.
 */
using SpringForceFcnPtr = double (*)(double R, const double* params, int lag_mastr_idx, int lag_slave_idx);

/*!
 * \brief Typedef specifying the spring force derivative function API.
 *
 * \return               The derivative with respect to R of the (undirected) "tension" force
 *generated by the spring.
 * \param R              The displacement between the "master" and "slave" nodes associated
 *with the
 *spring.
 * \param params         Constitutive parameters.
 * \param lag_mastr_idx  The Lagrangian index of the "master" node associated with the spring.
 * \param lag_slave_idx  The Lagrangian index of the "slave" node associated with the spring.
 */
using SpringForceDerivFcnPtr = double (*)(double R, const double* params, int lag_mastr_idx, int lag_slave_idx);

/*!
 * \brief Function to compute the (undirected) "tension" force generated by a
 * Hookean spring with either a zero or a non-zero resting length.
 *
 * Consider a single spring, and let \f$ k \f$ be the index of the "master" node
 * and \f$ l \f$ the index of the "slave" node.  The forces generated are \f[
 *
 *      \vec{F}_k = \kappa_{k,l} \left( \|\vec{X}_{l} - \vec{X}_{k}\| - r_{k,l} \right)
 *\frac{\vec{X}_{l} - \vec{X}_{k}}{\|\vec{X}_{l} - \vec{X}_{k}\|},
 *
 * \f] and \f[
 *
 *      \vec{F}_l = \kappa_{k,l} \left( \|\vec{X}_{l} - \vec{X}_{k}\| - r_{k,l} \right)
 *\frac{\vec{X}_{k} - \vec{X}_{l}}{\|\vec{X}_{l} - \vec{X}_{k}\|} = - \vec{F}_k,
 *
 * \f] where \f$ \kappa_{k,l} \f$ is the stiffness of the spring connecting
 * nodes \f$ k \f$ and \f$ l \f$, and where \f$ r_{k,l} \f$ is the associated
 * resting length of the spring.
 *
 * This function computes the undirected spring "tension" force \f$ T_{k,l} \f$
 * associated with these forces, \f[
 *
 *      T_{k,l} = \kappa_{k,l} \left( \|\vec{X}_{l} - \vec{X}_{k}\| - r_{k,l} \right).
 *
 * \f] \f$ T_{k,l} \f$ is used to compute the \em directed spring forces by
 * IBStandardForceGen via as \f[
 *
 *      \vec{F}_k = T_{k,l} \frac{\vec{X}_{l} - \vec{X}_{k}}{\|\vec{X}_{l} - \vec{X}_{k}\|}
 *
 * \f] and \f[
 *
 *      \vec{F}_l = T_{k,l} \frac{\vec{X}_{k} - \vec{X}_{l}}{\|\vec{X}_{k} - \vec{X}_{l}\|}.
 *
 * \f]
 *
 * \return               The (undirected) "tension" force generated by the spring.
 * \param R              The displacement between the "master" and "slave" nodes associated
 *with the
 *spring.
 * \param params         Constitutive parameters.
 * \param lag_mastr_idx  The Lagrangian index of the "master" node associated with the spring.
 * \param lag_slave_idx  The Lagrangian index of the "slave" node associated with the spring.
 *
 * \note This is the default force generation function employed by class
 * IBStandardForceGen.  It is associated with \a force_fcn_idx \a 0.  Users may
 * override this default value with any function that implements the interface
 * required by IBStandardForceGen::registerSpringForceFunction().
 */
inline double
default_spring_force(double R, const double* params, int /*lag_mastr_idx*/, int /*lag_slave_idx*/)
{
    return params[0] * (R - params[1]);
} // default_spring_force

/*!
 * \brief Function to compute the derivative with respect to R of the tension
 * force generated by a Hookean spring with either a zero or a non-zero resting
 * length.
 */
inline double
default_spring_force_deriv(double /*R*/, const double* params, int /*lag_mastr_idx*/, int /*lag_slave_idx*/)
{
    return params[0];
} // default_spring_force_deriv

} // namespace IBAMR

//////////////////////////////////////////////////////////////////////////////

#endif // #ifndef included_IBAMR_IBSpringForceFunctions
