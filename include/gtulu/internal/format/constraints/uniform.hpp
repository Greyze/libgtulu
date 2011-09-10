/**
 * @file
 *
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
 *
 * @date 19 déc. 2009
 * @todo comment
 */

#ifndef GTULU_INTERNAL_FORMAT_CONSTRAINT_UNIFORM_HPP_
#define GTULU_INTERNAL_FORMAT_CONSTRAINT_UNIFORM_HPP_

#include "gtulu/internal/format/constraints/common.hpp"

#include "gtulu/internal/format/uniform.hpp"
#include "gtulu/internal/format/internal.hpp"
#include "gtulu/internal/format/target.hpp"

#include "gtulu/internal/format/conversions/internal.hpp"

namespace gtulu {
  namespace internal {
    namespace bm = ::boost::mpl;

    namespace format {
      namespace uniform {
        namespace sampler {

          template< typename SamplerFormat, typename InternalFormat >
          struct shadow_stencil_check {
              typedef bm::or_< fc::component::is_depth< InternalFormat >,
                  fc::component::is_depth_stencil< InternalFormat > > shadow_capable_c;
              typedef bm::not_< bm::and_< fc::compare::is_shadow< SamplerFormat >, shadow_capable_c > > shadow_c;
              static_assert(shadow_c::value, "shadow uniform sampler only supports depth or depth_stencil InternalFormat.");

              typedef bm::not_< fc::component::is_stencil< InternalFormat > > stencil_c;
              static_assert(shadow_c::value, "uniform sampler does not support stencil InternalFormat.");

              typedef bm::and_< shadow_c, stencil_c > type;
          };

          template< typename SamplerFormat, typename InternalFormat >
          struct internal_type_check {
              typedef bm::or_< fn::integral::is_floating< typename fc::get_numeric< InternalFormat >::type >,
                  fn::integral::is_fixed< typename fc::get_numeric< InternalFormat >::type > > is_internal_floating;

              typedef bm::and_< is_internal_floating,
                  fn::integral::is_floating< typename fc::get_numeric< SamplerFormat >::type > > are_both_floating;
              typedef bm::and_< fn::integral::is_integral< typename fc::get_numeric< InternalFormat >::type >,
                  fn::integral::is_integral< typename fc::get_numeric< SamplerFormat >::type > > are_both_integer;
              typedef bm::and_< fn::sign::is_signed_< typename fc::get_numeric< InternalFormat >::type >,
                  fn::sign::is_signed_< typename fc::get_numeric< SamplerFormat >::type > > are_both_signed;
              typedef bm::and_< fn::sign::is_unsigned_< typename fc::get_numeric< InternalFormat >::type >,
                  fn::sign::is_unsigned_< typename fc::get_numeric< SamplerFormat >::type > > are_both_unsigned;
              typedef bm::and_< are_both_integer, bm::or_< are_both_signed, are_both_unsigned > > are_both_same_integral;

              typedef bm::or_< are_both_floating, are_both_same_integral > type;
              static_assert(type::value, "internal_type_t is not compatible with uniform sampler_type_t, floating sampler require floating, fixed or unsigned_fixed internal type, integer sampler require integer internal type and ::std::uint32_teger sampler require ::std::uint32_teger internal type.");
          };

          template< typename SamplerTargetFormat, typename TextureTargetFormat >
          struct is_target_same {
              typedef ::std::is_same< SamplerTargetFormat, TextureTargetFormat > type;
              static_assert(type::value, "SamplerTargetFormat and TextureTargetFormat are not same.");
          };

          template< typename SamplerFormat, typename TextureFormat >
          struct is_texture_compatible {
              typedef typename shadow_stencil_check< SamplerFormat, typename TextureFormat::internal >::type shadow_stencil_c;
              typedef typename internal_type_check< SamplerFormat, typename TextureFormat::internal >::type internal_type_c;
              typedef typename is_target_same< typename SamplerFormat::info::target, typename TextureFormat::target >::type target_same_c;

              typedef bm::and_< shadow_stencil_c, internal_type_c, target_same_c > type;
          };
        } // namespace sampler
      } // namespace uniform
    } // namespace format

  } // namespace internal
} // namespace gtulu

#endif /* GTULU_INTERNAL_FORMAT_CONSTRAINT_UNIFORM_HPP_ */
