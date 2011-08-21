/**
 * @file
 *
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
 *
 * @date 19 déc. 2009
 * @todo comment
 */

#ifndef GTULU_INTERNAL_FORMAT_INTERNAL_HPP_
#define GTULU_INTERNAL_FORMAT_INTERNAL_HPP_

#include "gtulu/internal/constants_fwd.hpp"

#include "gtulu/internal/formats/common.hpp"

namespace gtulu {
  namespace internal {

    namespace formats {
      namespace internal {

        namespace format {
          using cst::gl_r8;
          using cst::gl_r8_snorm;
          using cst::gl_r16;
          using cst::gl_r16_snorm;
          using cst::gl_rg8;
          using cst::gl_rg8_snorm;
          using cst::gl_rg16;
          using cst::gl_rg16_snorm;
          using cst::gl_r3_g3_b2;
          using cst::gl_rgb4;
          using cst::gl_rgb5;
          using cst::gl_rgb8;
          using cst::gl_rgb8_snorm;
          using cst::gl_rgb10;
          using cst::gl_rgb12;
          using cst::gl_rgb16;
          using cst::gl_rgb16_snorm;
          using cst::gl_rgba2;
          using cst::gl_rgba4;
          using cst::gl_rgb5_a1;
          using cst::gl_rgba8;
          using cst::gl_rgba8_snorm;
          using cst::gl_rgb10_a2;
          using cst::gl_rgba12;
          using cst::gl_rgba16;
          using cst::gl_rgba16_snorm;
          using cst::gl_srgb8;
          using cst::gl_srgb8_alpha8;
          using cst::gl_r16f;
          using cst::gl_rg16f;
          using cst::gl_rgb16f;
          using cst::gl_rgba16f;
          using cst::gl_r32f;
          using cst::gl_rg32f;
          using cst::gl_rgb32f;
          using cst::gl_rgba32f;
          using cst::gl_r11f_g11f_b10f;
          using cst::gl_rgb9_e5;
          using cst::gl_r8i;
          using cst::gl_r8ui;
          using cst::gl_r16i;
          using cst::gl_r16ui;
          using cst::gl_r32i;
          using cst::gl_r32ui;
          using cst::gl_rg8i;
          using cst::gl_rg8ui;
          using cst::gl_rg16i;
          using cst::gl_rg16ui;
          using cst::gl_rg32i;
          using cst::gl_rg32ui;
          using cst::gl_rgb8i;
          using cst::gl_rgb8ui;
          using cst::gl_rgb16i;
          using cst::gl_rgb16ui;
          using cst::gl_rgb32i;
          using cst::gl_rgb32ui;
          using cst::gl_rgba8i;
          using cst::gl_rgba8ui;
          using cst::gl_rgba16i;
          using cst::gl_rgba16ui;
          using cst::gl_rgba32i;
          using cst::gl_rgba32ui;
          typedef cst::gl_depth_component16 gl_depth16;
          typedef cst::gl_depth_component24 gl_depth24;
          typedef cst::gl_depth_component32 gl_depth32;
          typedef cst::gl_depth_component32f gl_depth32f;
          using cst::gl_depth24_stencil8;
          using cst::gl_depth32f_stencil8;
          using cst::gl_compressed_red;
          using cst::gl_compressed_rg;
          using cst::gl_compressed_rgb;
          using cst::gl_compressed_rgba;
          using cst::gl_compressed_srgb;
          using cst::gl_compressed_srgb_alpha;
          using cst::gl_compressed_red_rgtc1;
          using cst::gl_compressed_signed_red_rgtc1;
          using cst::gl_compressed_rg_rgtc2;
          using cst::gl_compressed_signed_rg_rgtc2;
          typedef cst::gl_stencil_index1 gl_stencil1;
          typedef cst::gl_stencil_index4 gl_stencil4;
          typedef cst::gl_stencil_index8 gl_stencil8;
          typedef cst::gl_stencil_index16 gl_stencil16;
        } // namespace format

        DECLARE_TRAIT_ASPECT(base, struct, (depth) (stencil) (depth_stencil) (r) (rg) (rgb) (rgba))
        DECLARE_TRAIT_ASPECT(type, struct, (floating) (fixed) (unsigned_fixed) (integer) (unsigned_integer))
        DECLARE_TRAIT_ASPECT(compression, struct, (normal) (compressed))
        DECLARE_TRAIT_ASPECT(restriction, struct, (unknown) (any) (texture) (renderbuffer))

        typedef ::std::uint32_t size_type;

        template< typename Format, typename Base, size_type Size, typename DataType, typename Compression,
            typename Restriction >
        struct internal_format_metadata {
            typedef Format format;
            typedef Base base;
            typedef DataType type;
            typedef Compression compression;
            typedef Restriction restriction;
            static size_type const size_ = Size;
        };

        template< typename Format >
        struct internal_format;

        template< typename Base, size_type Size, typename DataType, typename Compression >
        struct format_selector;

#define DECLARE_INTERNAL_FORMAT(format_m, base_m, size_m, type_m, compression_m, restriction_m) \
    template< > struct internal_format< format::format_m > { \
        typedef internal_format_metadata< format::format_m, \
                                          base::base_m, \
                                          size_m, \
                                          type::type_m, \
                                          compression::compression_m, \
                                          restriction::restriction_m > info; \
    }; \
    typedef internal_format< format::format_m > format_m; \
    DECLARE_HAS_TRAIT_FORMAT(base, base_m, format_m); \
    DECLARE_HAS_TRAIT_FORMAT(type, type_m, format_m); \
    DECLARE_HAS_TRAIT_FORMAT(compression, compression_m, format_m); \
    DECLARE_HAS_TRAIT_FORMAT(restriction, restriction_m, format_m); \

#define DECLARE_INTERNAL_FORMAT_DEFAULT(format_m, base_m, size_m, type_m, compression_m, restriction_m) \
    DECLARE_INTERNAL_FORMAT(format_m, base_m, size_m, type_m, compression_m, restriction_m) \
    template< > struct format_selector< base::base_m, \
                                        size_m, \
                                        type::type_m, \
                                        compression::compression_m > { \
        typedef format_m format; \
    };

        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_r8, r, 8, unsigned_fixed, normal, any)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_r8_snorm, r, 8, fixed, normal, texture)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_r16, r, 16, unsigned_fixed, normal, any)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_r16_snorm, r, 16, fixed, normal, texture)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_rg8, rg, 8, unsigned_fixed, normal, any)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_rg8_snorm, rg, 8, fixed, normal, texture)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_rg16, rg, 16, unsigned_fixed, normal, any)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_rg16_snorm, rg, 16, fixed, normal, texture)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_r3_g3_b2, rgb, 3, unsigned_fixed, normal, unknown)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_rgb4, rgb, 4, unsigned_fixed, normal, unknown)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_rgb5, rgb, 5, unsigned_fixed, normal, unknown)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_rgb8, rgb, 8, unsigned_fixed, normal, texture)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_rgb8_snorm, rgb, 8, fixed, normal, texture)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_rgb10, rgb, 10, unsigned_fixed, normal, unknown)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_rgb12, rgb, 12, unsigned_fixed, normal, unknown)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_rgb16, rgb, 16, unsigned_fixed, normal, texture)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_rgb16_snorm, rgb, 16, fixed, normal, texture)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_rgba2, rgba, 2, unsigned_fixed, normal, unknown)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_rgba4, rgba, 4, unsigned_fixed, normal, unknown)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_rgb5_a1, rgba, 5, unsigned_fixed, normal, unknown)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_rgba8, rgba, 8, unsigned_fixed, normal, any)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_rgba8_snorm, rgba, 8, fixed, normal, texture)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_rgb10_a2, rgba, 10, unsigned_fixed, normal, any)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_rgba12, rgba, 12, unsigned_fixed, normal, unknown)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_rgba16, rgba, 16, unsigned_fixed, normal, any)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_rgba16_snorm, rgba, 16, fixed, normal, texture)
        DECLARE_INTERNAL_FORMAT(gl_srgb8, rgb, 8, unsigned_fixed, normal, texture)
        DECLARE_INTERNAL_FORMAT(gl_srgb8_alpha8, rgba, 8, unsigned_fixed, normal, any)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_r16f, r, 16, floating, normal, any)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_rg16f, rg, 16, floating, normal, any)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_rgb16f, rgb, 16, floating, normal, texture)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_rgba16f, rgba, 16, floating, normal, any)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_r32f, r, 32, floating, normal, any)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_rg32f, rg, 32, floating, normal, any)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_rgb32f, rgb, 32, floating, normal, texture)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_rgba32f, rgba, 32, floating, normal, any)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_r11f_g11f_b10f, rgb, 11, floating, normal, any)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_rgb9_e5, rgb, 9, unsigned_fixed, normal, texture)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_r8i, r, 8, integer, normal, any)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_r8ui, r, 8, unsigned_integer, normal, any)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_r16i, r, 16, integer, normal, any)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_r16ui, r, 16, unsigned_integer, normal, any)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_r32i, r, 32, integer, normal, any)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_r32ui, r, 32, unsigned_integer, normal, any)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_rg8i, rg, 8, integer, normal, any)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_rg8ui, rg, 8, unsigned_integer, normal, any)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_rg16i, rg, 16, integer, normal, any)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_rg16ui, rg, 16, unsigned_integer, normal, any)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_rg32i, rg, 32, integer, normal, any)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_rg32ui, rg, 32, unsigned_integer, normal, any)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_rgb8i, rgb, 8, integer, normal, texture)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_rgb8ui, rgb, 8, unsigned_integer, normal, texture)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_rgb16i, rgb, 16, integer, normal, texture)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_rgb16ui, rgb, 16, unsigned_integer, normal, texture)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_rgb32i, rgb, 32, integer, normal, texture)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_rgb32ui, rgb, 32, unsigned_integer, normal, texture)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_rgba8i, rgba, 8, integer, normal, any)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_rgba8ui, rgba, 8, unsigned_integer, normal, any)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_rgba16i, rgba, 16, integer, normal, any)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_rgba16ui, rgba, 16, unsigned_integer, normal, any)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_rgba32i, rgba, 32, integer, normal, any)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_rgba32ui, rgba, 32, unsigned_integer, normal, any)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_depth16, depth, 16, unsigned_fixed, normal, unknown)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_depth24, depth, 24, unsigned_fixed, normal, unknown)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_depth32, depth, 32, unsigned_fixed, normal, unknown)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_depth32f, depth, 32, floating, normal, unknown)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_depth24_stencil8, depth_stencil, 24, unsigned_fixed, normal, unknown)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_depth32f_stencil8, depth_stencil, 32, floating, normal, unknown)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_compressed_red, r, 8, unsigned_fixed, compressed, unknown)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_compressed_rg, rg, 8, unsigned_fixed, compressed, unknown)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_compressed_rgb, rgb, 8, unsigned_fixed, compressed, unknown)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_compressed_rgba, rgba, 8, unsigned_fixed, compressed, unknown)
        DECLARE_INTERNAL_FORMAT(gl_compressed_srgb, rgb, 8, unsigned_fixed, compressed, unknown)
        DECLARE_INTERNAL_FORMAT(gl_compressed_srgb_alpha, rgba, 8, unsigned_fixed, compressed, unknown)
        DECLARE_INTERNAL_FORMAT(gl_compressed_red_rgtc1, r, 8, unsigned_fixed, compressed, texture)
        DECLARE_INTERNAL_FORMAT(gl_compressed_signed_red_rgtc1, r, 8, unsigned_fixed, compressed, texture)
        DECLARE_INTERNAL_FORMAT(gl_compressed_rg_rgtc2, rg, 8, unsigned_fixed, compressed, texture)
        DECLARE_INTERNAL_FORMAT(gl_compressed_signed_rg_rgtc2, rg, 8, unsigned_fixed, compressed, texture)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_stencil1, stencil, 1, unsigned_fixed, normal, renderbuffer)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_stencil4, stencil, 4, unsigned_fixed, normal, renderbuffer)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_stencil8, stencil, 8, unsigned_fixed, normal, renderbuffer)
        DECLARE_INTERNAL_FORMAT_DEFAULT(gl_stencil16, stencil, 16, unsigned_fixed, normal, renderbuffer)

#undef DECLARE_INTERNAL_FORMAT_DEFAULT
#undef DECLARE_INTERNAL_FORMAT

        template< typename Format > struct base_internal_format;
#define DECLARE_BASE_INTERNAL_FORMAT(base_m, size_m, type_m, compressed_m) \
    typedef format_selector< base::base_m, size_m, type::type_m, compression::compressed_m >::format base_m; \

        DECLARE_BASE_INTERNAL_FORMAT(r, 8, unsigned_fixed, normal)
        DECLARE_BASE_INTERNAL_FORMAT(rg, 8, unsigned_fixed, normal)
        DECLARE_BASE_INTERNAL_FORMAT(rgb, 8, unsigned_fixed, normal)
        DECLARE_BASE_INTERNAL_FORMAT(rgba, 8, unsigned_fixed, normal)
        DECLARE_BASE_INTERNAL_FORMAT(depth, 16, unsigned_fixed, normal)
        DECLARE_BASE_INTERNAL_FORMAT(depth_stencil, 24, unsigned_fixed, normal)
        DECLARE_BASE_INTERNAL_FORMAT(stencil, 8, unsigned_fixed, normal)

#undef DECLARE_BASE_INTERNAL_FORMAT

      } // namespace internal
    } // namespace formats

    namespace fi = ::gtulu::internal::formats::internal;
    namespace fib = ::gtulu::internal::formats::internal::base;
    namespace fic = ::gtulu::internal::formats::internal::compression;
    namespace fif = ::gtulu::internal::formats::internal::format;
    namespace fit = ::gtulu::internal::formats::internal::type;
    namespace fir = ::gtulu::internal::formats::internal::restriction;

  } // namespace internal
} // namespace gtulu

#endif /* GTULU_INTERNAL_FORMAT_INTERNAL_HPP_ */
