// Copyright (c) 2018-2019 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/config/

#ifndef TAO_CONFIG_PARSE_FILE_HPP
#define TAO_CONFIG_PARSE_FILE_HPP

#include <string>
#include <utility>

#include "value.hpp"

#include "schema/builtin.hpp"

#include "internal/configurator.hpp"

namespace tao::config
{
   template< template< typename... > class Traits >
   json::basic_value< Traits > basic_parse_file( const std::string& filename, schema::builtin b = schema::builtin() )
   {
      return internal::configurator().parse( filename ).process< Traits >( std::move( b ) );
   }

   inline value parse_file( const std::string& filename, schema::builtin b = schema::builtin() )
   {
      return basic_parse_file< traits >( filename, std::move( b ) );
   }

}  // namespace tao::config

#endif
