/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */
#ifndef _ORG_JAVOLUTION_INTERNAL_OSGI_FILTER_IMPL_HPP
#define _ORG_JAVOLUTION_INTERNAL_OSGI_FILTER_IMPL_HPP

#include "java/lang/Object.hpp"
#include "java/lang/String.hpp"
#include "java/lang/RuntimeException.hpp"
#include "java/lang/UnsupportedOperationException.hpp"
#include "org/osgi/framework/Constants.hpp"
#include "org/osgi/framework/Filter.hpp"
#include "org/javolution/internal/osgi/ServiceReferenceImpl.hpp"

using namespace java::lang;
using namespace org::javolution::util;
using namespace org::javolution::internal::osgi;
using namespace org::osgi::framework;

namespace org { namespace javolution { namespace internal { namespace osgi {
    class FilterImpl_API;
    typedef Type::Handle<FilterImpl_API> FilterImpl;
}}}}

/**
 * Filter implementation (value type).
 *
 * @version 1.0
 */
class org::javolution::internal::osgi::FilterImpl_API : public virtual Filter_API {
public: // Internal classes can have public members visibility.

    String _className;
    String _filterString;

    FilterImpl_API(String const& filterString) {
        _filterString = filterString;
        if (!filterString->startsWith(Constants_API::OBJECTCLASS, 1))
            throw UnsupportedOperationException_API::newInstance();
        // Filter is : "(<Constants_API::OBJECT_CLASS>=<className>)"
        Type::int32 classNameStartIndex = Constants_API::OBJECTCLASS->length() + 2;
        _className = filterString->substring(classNameStartIndex, filterString->length() - 1);
    }

    Type::boolean match(ServiceReference const& reference) const {
        ServiceReferenceImpl sri = Type::dynamic_handle_cast<ServiceReferenceImpl_API > (reference);
        return sri->_serviceName->equals(_className);
    }

    String toString() const {
        return _filterString;
    }
};
#endif
