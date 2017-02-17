/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */
#pragma once

#include <sstream>
#include "java/lang/Object.hpp"
#include "java/lang/String.hpp"
#include "java/lang/Boolean.hpp"
#include "java/lang/Character.hpp"
#include "java/lang/IllegalArgumentException.hpp"
#include "java/lang/IndexOutOfBoundsException.hpp"
#include "java/lang/Integer.hpp"
#include "java/lang/Long.hpp"
#include "java/lang/Float.hpp"
#include "java/lang/Double.hpp"

namespace java {
namespace lang {

/**
 * This class represents a mutable sequence of characters.
 *
 * @see  <a href="https://docs.oracle.com/javase/8/docs/api/java/lang/StringBuilder.html">
 *       Java - StringBuilder</a>
 * @version 7.0
 */
class StringBuilder final : public virtual CharSequence {
public:
    StringBuilder(Void = nullptr) {}
    StringBuilder(Value* value) : Object(value) {}

    /** Constructs a new empty string builder. */
    static StringBuilder newInstance() {
        return new Value();
    }

    /**
     * Appends the textual representation of the specified object.
     */
    StringBuilder append(const Object& obj) {
        return append(String::valueOf(obj));
    }

    /**
     * Appends the specified string.
     */
    StringBuilder append(const String& str) {
        return this_<Value>()->append(str);
    }

    /**
     * Appends the specified int value.
     */
    StringBuilder append(int value) {
        std::wostringstream out;
        out << value;
        return append(out.str());
    }

    /**
     * Appends the specified long value.
     */
    StringBuilder append(long value) {
        std::wostringstream out;
        out << value;
        return append(out.str());
    }

    /**
     * Appends the specified long long value (at least 64 bits).
     */
    StringBuilder append(long long value) {
        std::wostringstream out;
        out << value;
        return append(out.str());
    }

    /**
     * Appends the specified 32 bits float value.
     */
    StringBuilder append(float value) {
        std::wostringstream out;
        out << value;
        return append(out.str());
    }

    /**
     * Appends the specified 64 bits float value.
     */
    StringBuilder append(double value) {
        std::wostringstream out;
        out << value;
        return append(out.str());
    }

    /**
     * Appends the specified C++ UTF-8 simple characters (null terminated).
     */
    StringBuilder append(const char* chars) {
        return this_<Value>()->append(chars);
    }

    /**
     * Appends the specified C++ wide characters (null terminated).
     */
    StringBuilder append(const Type::wchar* chars) {
        return this_<Value>()->append(chars);
    }

    /**
     * Appends the specified C++ wide string.
     */
    StringBuilder append(const std::wstring& wstr) {
        return append(wstr.c_str());
    }

    /**
     * Appends the specified C++ string (UTF-8).
     */
    StringBuilder append(const std::string& str) {
        return append(str.c_str());
    }

    /**
     * Appends the specified ASCII character.
     *
     * @throw IllegalArgumentException if the specified value is not ASCII
     */
    StringBuilder append(char ascii) {
        if (ascii > 127)
        throw IllegalArgumentException("Non-ASCII Character");
        return append((Type::wchar) ascii);
    }

    /**
     * Appends the specified wide character.
     */
    StringBuilder append(Type::wchar wc) {
        return this_<Value>()->append(wc);
    }

    /**
     * Appends the specified bool object.
     */
    StringBuilder append(bool value) {
        return append(value ? "true" : "false");
    }

    //////////////////
    // CharSequence //
    //////////////////

    Type::wchar charAt(int index) const {
        return this_<Value>()->charAt(index);
    }

    int length() const {
        return this_<Value>()->length();
    }

    CharSequence subSequence(int start, int end) const {
        return this_<Value>()->subSequence(start, end);
    }

    ////////////////////
    // Implementation //
    ////////////////////

    class Value final : public Object::Value, public virtual CharSequence::Interface {
        static const int WCHARS_INC = 32; // Smooth length increment.
        Array<Type::wchar> wchars = Array<Type::wchar>::newInstance();
        int count = 0;
        bool immutable = false;// Becomes immutable after toString() is called since the array will be shared.
    public:

        JAVOLUTION_DLL
        StringBuilder append(Type::wchar wc);

        JAVOLUTION_DLL
        StringBuilder append(const String& str);

        JAVOLUTION_DLL
        StringBuilder append(const char* chars);

        JAVOLUTION_DLL
        StringBuilder append(const Type::wchar* chars);

        Type::wchar charAt(int index) const override {
            if (index >= count)
            throw IndexOutOfBoundsException();
            return wchars[index];
        }

        int length() const override {
            return count;
        }

        CharSequence subSequence(int start, int end) const override {
            return toString().substring(start, end);
        }

        String toString() const override {
            Value* self = const_cast<Value*>(this); // Removes constness.
            self->wchars.length = count;// Ok, small reduction adjustment (no need to call setLength).
            self->immutable = true;
            return new String::Value(self->wchars); // Share the same array.
        }

    };

};
}
}
