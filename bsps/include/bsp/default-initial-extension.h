/**
 *  @file
 *
 *  @ingroup shared_defaultinitialextension
 *
 *  @brief DEFAULT_INITIAL_EXTENSION Support
 */

/*
 * Copyright (c) 2012 embedded brains GmbH.  All rights reserved.
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rtems.org/license/LICENSE.
 */

#ifndef LIBBSP_SHARED_DEFAULT_INITIAL_EXTENSION_H
#define LIBBSP_SHARED_DEFAULT_INITIAL_EXTENSION_H

#include <rtems.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 *  @defgroup shared_defaultinitialextension DEFAULT_INITIAL_EXTENSION Support
 *
 *  @ingroup RTEMSBSPsShared
 *
 *  @brief DEFAULT_INITIAL_EXTENSION Support Package
 */

void bsp_fatal_extension(
  rtems_fatal_source source,
  bool always_set_to_false,
  rtems_fatal_code error
);

#define BSP_INITIAL_EXTENSION \
  { NULL, NULL, NULL, NULL, NULL, NULL, NULL, bsp_fatal_extension, NULL }

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LIBBSP_SHARED_DEFAULT_INITIAL_EXTENSION_H */
