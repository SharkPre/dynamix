// DynaMix
// Copyright (c) 2013-2016 Borislav Stanimirov, Zahary Karadjov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once

/**
 * \file
 * Types related to mixin features.
 */

#include "global.hpp"

namespace dynamix
{

/// The type of the `none` feature.
struct DYNAMIX_API no_features_t {};

/// Use this as a mixin feature to indicate that the mixin
/// implements no features.
extern DYNAMIX_API no_features_t* none;

static const feature_id INVALID_FEATURE_ID = ~feature_id(0);

class DYNAMIX_API feature : public internal::noncopyable
{
public:
    feature_id id;
    const char* const name;

    bool is_private; // true when it's never used outside a single module
    // registrators will register features of the same name as the same feature
    // if they're not private
    // having different features with the same name in different modules
    // may cause dangerous crashes if they're not private

protected:
    feature(const char* name, bool is_private)
        : id(INVALID_FEATURE_ID)
        , name(name)
        , is_private(is_private)
    {
    }
};


namespace internal
{

// like the mixin_type_info_instance this class is as a
// metafunction to bind feature types to their unique instances
template <typename Feature>
struct feature_instance
{
    // using a static function instead of a member to guarantee the constructor is called
    static Feature& the_feature()
    {
        static Feature f;
        return f;
    }

    // unfortunately we cannot do the mixin trick of global instantiation here
    // there is no guarantee that the features will be instantiated before the mixins
    // and their id's are needed
    // instead we'll register the features manually when registering the mixin
    // this will be at the cost of having features registered multiple times
};

} // namespace internal
} // namespace dynamix
