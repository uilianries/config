// Copyright (c) 2018-2019 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/config/

#ifndef TAO_CONFIG_PARSE_FILES_HPP
#define TAO_CONFIG_PARSE_FILES_HPP

#include <string>
#include <utility>
#include <vector>

#include "value.hpp"

#include "schema/builtin.hpp"

#include "internal/configurator.hpp"

namespace tao::config
{
   template< template< typename... > class Traits >
   json::basic_value< Traits > basic_parse_files( const std::vector< std::string >& filenames, schema::builtin b = schema::builtin() )
   {
      internal::configurator c;
      for( const auto& filename : filenames ) {
         c.parse( pegtl::file_input( filename ) );
      }
      return c.process< Traits >( std::move( b ) );
   }

   inline value parse_files( const std::vector< std::string >& filenames, schema::builtin b = schema::builtin() )
   {
      return basic_parse_files< traits >( filenames, std::move( b ) );
   }

}  // namespace tao::config

#endif
