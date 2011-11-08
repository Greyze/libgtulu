/**
 * @file
 *
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef GTULU_INTERNAL_STORAGE_COPY_HPP_
#define GTULU_INTERNAL_STORAGE_COPY_HPP_

#include "gtulu/namespaces.hpp"

#include "gtulu/internal/object/buffer.hpp"
#include "gtulu/internal/storage/bind.hpp"
#include "gtulu/internal/storage/data/empty.hpp"
#include "gtulu/internal/storage/data/traits.hpp"

namespace gtulu {
  namespace internal {

    namespace storage {
      namespace detail {

        template< typename TargetStore, typename SourceStore >
        struct copier {
            typedef TargetStore target_store_t;
            typedef SourceStore source_store_t;

            typedef data::data_traits< target_store_t > target_traits_t;
            typedef data::data_traits< source_store_t > source_traits_t;

            static void copy(target_store_t& target_store, source_store_t const& source_store);
        };

        /* Buffer to Host */
        template< typename HostStore, typename DataFormat >
        struct copier< HostStore, obj::buffer< DataFormat > > {
            typedef HostStore target_store_t;
            typedef obj::buffer< DataFormat > source_store_t;

            typedef data::data_traits< target_store_t > target_traits_t;
            typedef data::data_traits< source_store_t > source_traits_t;

            static void copy(target_store_t& target_store, source_store_t const& source_store) {
              copy_binder< target_store_t, source_store_t >::bind(target_store, source_store);
            }
        };

        /* Host to Buffer */
        template< typename DataFormat, typename HostStore >
        struct copier< obj::buffer< DataFormat >, HostStore > {
            typedef obj::buffer< DataFormat > target_store_t;
            typedef HostStore source_store_t;

            typedef data::data_traits< target_store_t > target_traits_t;
            typedef data::data_traits< source_store_t > source_traits_t;

            static void copy(target_store_t& target_store, source_store_t const& source_store) {
              copy_binder< target_store_t, source_store_t >::bind(target_store, source_store);
            }
        };

        /* Buffer to Buffer */
        template< typename TargetDataFormat, typename SourceDataFormat >
        struct copier< obj::buffer< TargetDataFormat >, obj::buffer< SourceDataFormat > > {
            typedef obj::buffer< TargetDataFormat > target_store_t;
            typedef obj::buffer< SourceDataFormat > source_store_t;

            typedef data::data_traits< target_store_t > target_traits_t;
            typedef data::data_traits< source_store_t > source_traits_t;

            static void copy(target_store_t& target_store, source_store_t const& source_store) {
              copy_binder< target_store_t, source_store_t >::bind(target_store, source_store);
            }
        };

        /* Texture to Host */
        template< typename HostStore, typename TextureFormat >
        struct copier< HostStore, obj::texture< TextureFormat > > {
            typedef HostStore target_store_t;
            typedef obj::texture< TextureFormat > source_store_t;

            typedef data::data_traits< target_store_t > target_traits_t;
            typedef data::data_traits< source_store_t > source_traits_t;

            static void copy(target_store_t& target_store, source_store_t const& source_store) {
              copy_binder< target_store_t, source_store_t >::bind(target_store, source_store);
              detail::texture::copy(target_store, source_store);
            }
        };

        /* Host to Texture */
        template< typename TextureFormat, typename HostStore >
        struct copier< obj::texture< TextureFormat >, HostStore > {
            typedef obj::texture< TextureFormat > target_store_t;
            typedef HostStore source_store_t;

            typedef data::data_traits< target_store_t > target_traits_t;
            typedef data::data_traits< source_store_t > source_traits_t;

            static void copy(target_store_t& target_store, source_store_t const& source_store) {
              copy_binder< target_store_t, source_store_t >::bind(target_store, source_store);
              detail::texture::copy(target_store, source_store);
            }
        };

        /* Texture to Buffer */
        template< typename DataFormat, typename TextureFormat >
        struct copier< obj::buffer< DataFormat >, obj::texture< TextureFormat > > {
            typedef obj::buffer< DataFormat > target_store_t;
            typedef obj::texture< TextureFormat > source_store_t;

            typedef data::data_traits< target_store_t > target_traits_t;
            typedef data::data_traits< source_store_t > source_traits_t;

            static void copy(target_store_t& target_store, source_store_t const& source_store) {
              copy_binder< target_store_t, source_store_t >::bind(target_store, source_store);
              detail::texture::copy(target_store, source_store);
            }
        };

        /* Buffer to Texture */
        template< typename TextureFormat, typename DataFormat >
        struct copier< obj::texture< TextureFormat >, obj::buffer< DataFormat > > {
            typedef obj::texture< TextureFormat > target_store_t;
            typedef obj::buffer< DataFormat > source_store_t;

            typedef data::data_traits< target_store_t > target_traits_t;
            typedef data::data_traits< source_store_t > source_traits_t;

            static void copy(target_store_t& target_store, source_store_t const& source_store) {
              copy_binder< target_store_t, source_store_t >::bind(target_store, source_store);
              detail::texture::copy(target_store, source_store);
            }
        };

      } // namespace detail

      template< typename TargetStore, typename SourceStore >
      void copy(TargetStore& target_store, SourceStore const& source_store) {
        detail::copier< TargetStore, SourceStore >::copy(target_store, source_store);
      }

    } // namespace storage

  } // namespace internal
} // namespace gtulu

#endif /* GTULU_INTERNAL_STORAGE_COPY_HPP_ */