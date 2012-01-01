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

// Maintain backward compatibility with releases prior to 1.0
#if ARDUINO < 100
#include <WProgram.h>
#else
#include <Arduino.h>
#endif

#ifndef JOINT_H
#define JOINT_H

#define DEBUG  true

class Joint {
  private:
    int number;
    int pos;
    String command;
    
  public:
    Joint() { number = 1; pos = 0; command = ""; };
    Joint(int n, int p);
    void move(int time);
    void cancel();
    void update(int p);
    
    int to_uS(int degree){  return (degree * 10) + 1500;  }
    
    void setNumber(int n) { number = n; }
    void setPosition(int p) { pos = to_uS(p); }
    
    int getNumber() { return number; }
    int getPosition() { return pos; }
    String getCommand() { return command; }
};

#endif
