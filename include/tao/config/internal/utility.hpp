// Copyright (c) 2018-2019 Dr. Colin Hirsch and Daniel Frey
// Please see LICENSE for license or visit https://github.com/taocpp/config/

#ifndef TAO_CONFIG_INTERNAL_UTILITY_HPP
#define TAO_CONFIG_INTERNAL_UTILITY_HPP

#include <cassert>
#include <stdexcept>

#include "../key.hpp"

#include "format.hpp"
#include "json.hpp"

namespace tao
{
   namespace config
   {
      namespace internal
      {
         template< typename Container >
         struct reverse
         {
            explicit reverse( Container& l )
               : m_c( l )
            {
            }

            reverse( reverse&& ) = delete;
            reverse( const reverse& ) = delete;

            void operator=( reverse&& ) = delete;
            void operator=( const reverse& ) = delete;

            auto begin()
            {
               return m_c.rbegin();
            }

            auto end()
            {
               return m_c.rend();
            }

         private:
            Container& m_c;
         };

         template< typename T >
         reverse( T& )->reverse< T >;

         template< template< typename... > class Traits >
         part part_from_value( const position& pos, const json::basic_value< Traits >& v )
         {
            switch( v.type() ) {
               case json::type::BOOLEAN:
                  return part( v.unsafe_get_boolean() ? part::star : part::minus );
               case json::type::STRING:
               case json::type::STRING_VIEW:
                  return part( v.template as< std::string >() );
               case json::type::SIGNED:
               case json::type::UNSIGNED:
                  return part( v.template as< std::size_t >() );
               default:
                  throw std::runtime_error( format( "invalid json for part -- expected string or integer (or bool)", { &pos, v.type() } ) );
            }
         }

         template< template< typename... > class Traits >
         key key_from_value( const position& pos, json::basic_value< Traits >& v )
         {
            key p;

            if( v.is_string() ) {
               p.emplace_back( part( v.unsafe_get_string() ) );
               return p;
            }
            if( !v.is_array() ) {
               throw std::runtime_error( format( "invalid json for key -- expected array", { &pos, v.type() } ) );
            }
            for( const auto& t : v.unsafe_get_array() ) {
               p.emplace_back( part_from_value( pos, t ) );
            }
            v.discard();
            return p;
         }

      }  // namespace internal

   }  // namespace config

}  // namespace tao

#endif
