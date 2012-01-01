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

#include "joint.h"

#ifndef JOINTS_H
#define JOINTS_H

class Joints{
  private:
    Joint* joints[32];
    int _length;
    String command;
  
  public:
    Joints() { _length = 0; }
    Joints(Joint* jointset[], int len) { setJoints(jointset, len); }
    void setJoints(Joint* jointset[], int len);
    void appendJoint(Joint* joint);
    void removeJoint();
    String getCommand(){ return command; }
    void setCommand(String cmd) { command = cmd; }
    int getLength() { return _length; }
    void setLength(int l) { _length = l; }
    
    void update();
    void move(int time);
    void cancel();
};

#endif
