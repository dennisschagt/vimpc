/*
   Vimpc
   Copyright (C) 2010 Nathan Sweetman

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.

   callback.hpp - 
   */

#ifndef __UI__CALLBACK
#define __UI__CALLBACK

#include <stdint.h>

#include "boost/function.hpp"

#include "window.hpp"

namespace Main
{
   //! Object to wrap the callback function
   template <class Object, class Parameter>
   class CallbackObject
   {
      private: 
         typedef void (Object::*CallbackFunction)(Parameter &);

      public:
         CallbackObject(Object & callee, CallbackFunction callback) :
            callee_   (callee),
            callback_ (callback)
         { }

         void operator() (Parameter & param) { (callee_.*callback_)(param); }

      private:
         Object & callee_;
         CallbackFunction callback_;
   };

   //! Object to wrap the callback function
   template <class Parameter>
   class CallbackObject<void, Parameter>
   {
      private: 
         typedef void (*CallbackFunction)(Parameter &);

      public:
         CallbackObject(CallbackFunction callback) :
            callback_ (callback)
         { }

         void operator() (Parameter & param) { (*callback_)(param); }

      private:
         CallbackFunction callback_;
   };
}

#endif