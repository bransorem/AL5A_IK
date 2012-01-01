/* Copyright (C) 2011 Brannen Sorem. All rights reserved.

This software may be distributed and modified under the terms of the GNU
General Public License version 2 (GPL2) as published by the Free Software
Foundation and appearing in the file GPL2.TXT included in the packaging of
this file. Please note that GPL2 Section 2[b] requires that all works based
on this software must also be made publicly available under the terms of
the GPL2 ("Copyleft").

Contact information
-------------------

Author   :  Brannen Sorem
Web      :  http://www.bransorem.com
e-mail   :  contact@bransorem.com
*/

#include "joints.h"

#ifndef ARM_H
#define ARM_H

// CONSTANTS of arm measurements
// Dimensions (in mm)
#define BASE_HEIGHT   69.85    // base height 2.75"
#define HUMERUS       95.25    // shoulder-to-elbow  3.75"
#define ULNA          107.95   // elbow-to-wrist  4.25"
#define GRIPPER       85.725   // 3.375"
#define GRIP_ANGLE    0

#define d3            0
#define d4            0
#define a1            BASE_HEIGHT
#define a2            HUMERUS
#define a3            ULNA
#define a4            GRIPPER
#define r13           0
#define r23           0
#define r33           0


class Arm{
  private:
    Joint base;        // base (rotates)
    Joint shoulder;    // shoulder
    Joint elbow;       // elbow
    Joint wrist;       // wrist
    Joint wrist_rotate;// wrist rotate
    Joint gripper;     // gripper

    Joint* array[6];
    Joints arm;

  public:
    Arm();
    // Cartesian-space
    // X Y Z input
    void move(float x, float y, float z, int t);
    // Joint-space
    // Manual control (degrees for each servo input)
    void move(float b, float s, float e, float w, float wr, float g, int t);
    // Cancel current operation.  May not work due to delay in move command
    void cancel();
    void test();
};

#endif
