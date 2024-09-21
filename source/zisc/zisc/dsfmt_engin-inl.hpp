/*!
 \file dsfmt_engin-inl.hpp
 \author takemura
 */

#ifndef _ZISC_DSFMT_ENGIN_INL_HPP_
#define _ZISC_DSFMT_ENGIN_INL_HPP_

#include "dsfmt_engin.hpp"
// Standard C++ library
#include <cstddef>
#include <cstdint>
#include <type_traits>
// Zisc
#include "utility.hpp"
#include "type_traits.hpp"

namespace zisc {

/*!
 \details
 No detailed.
 */
template <std::size_t kN, std::size_t kPosition, int kSl,
          std::uint64_t kMask1, std::uint64_t kMask2, std::uint64_t kFix1, 
          std::uint64_t kFix2, std::uint64_t kPcv1, std::uint64_t kPcv2> inline
DsfmtEngin<kN, kPosition, kSl, kMask1, kMask2, kFix1, kFix2, kPcv1, kPcv2>::
DsfmtEngin() :
    index_{kN * 2},
    random_list_{&status_[0].d_[0]}
{
  setSeed(0);
}
  
/*!
 \details
 No detailed.
 */
template <std::size_t kN, std::size_t kPosition, int kSl,
          std::uint64_t kMask1, std::uint64_t kMask2, std::uint64_t kFix1, 
          std::uint64_t kFix2, std::uint64_t kPcv1, std::uint64_t kPcv2> inline
double DsfmtEngin<kN, kPosition, kSl, kMask1, kMask2, kFix1, kFix2, kPcv1, kPcv2>::
operator()()
{
  return generate();
}

namespace inner {

/*!
  \details
  No detailed.
  */
template <std::size_t kN, std::size_t kPosition, int kSl,
          std::uint64_t kMask1, std::uint64_t kMask2, std::uint64_t kFix1, 
          std::uint64_t kFix2, std::uint64_t kPcv1, std::uint64_t kPcv2,
          typename Float, EnableIfFloat<Float> = kEnabler> inline 
Float dsfmtDistribute(const Float a, const Float b, 
    DsfmtEngin<kN, kPosition, kSl, kMask1, kMask2, kFix1, kFix2, kPcv1, kPcv2>& dsfmt)
{
  constexpr Float epsilon = std::numeric_limits<Float>::epsilon();
  return a + cast<Float>(dsfmt.generate() - 1.0) * ((b - epsilon) - a);
}

/*!
  \details
  No detailed.
  */
template <std::size_t kN, std::size_t kPosition, int kSl,
          std::uint64_t kMask1, std::uint64_t kMask2, std::uint64_t kFix1, 
          std::uint64_t kFix2, std::uint64_t kPcv1, std::uint64_t kPcv2,
          typename Integer, EnableIfInteger<Integer> = kEnabler> inline 
Integer dsfmtDistribute(const Integer a, const Integer b, 
    DsfmtEngin<kN, kPosition, kSl, kMask1, kMask2, kFix1, kFix2, kPcv1, kPcv2>& dsfmt)
{
  return a + cast<Integer>((dsfmt.generate() - 1.0) * cast<double>(b - a));
}

} // namespace inner

/*!
 \details
 No detailed.
 */
template <std::size_t kN, std::size_t kPosition, int kSl,
          std::uint64_t kMask1, std::uint64_t kMask2, std::uint64_t kFix1, 
          std::uint64_t kFix2, std::uint64_t kPcv1, std::uint64_t kPcv2> 
template <typename Arithmetic> inline
Arithmetic DsfmtEngin<kN, kPosition, kSl, kMask1, kMask2, kFix1, kFix2, kPcv1, kPcv2>
::distribute(const Arithmetic a, const Arithmetic b)
{
  static_assert(std::is_arithmetic<Arithmetic>::value,
                "## Arguments must be arithmetic type.");
  return inner::dsfmtDistribute(a, b, *this);
}

/*!
 \details
 No detailed.
 */
template <std::size_t kN, std::size_t kPosition, int kSl,
          std::uint64_t kMask1, std::uint64_t kMask2, std::uint64_t kFix1, 
          std::uint64_t kFix2, std::uint64_t kPcv1, std::uint64_t kPcv2> inline
double DsfmtEngin<kN, kPosition, kSl, kMask1, kMask2, kFix1, kFix2, kPcv1, kPcv2>::
generate()
{
  if (index_ == (kN * 2)) {
    generateRandomAll();
    index_ = 0;
  }
  return random_list_[index_++];
}

/*!
 \details
 No detailed.
 */
template <std::size_t kN, std::size_t kPosition, int kSl,
          std::uint64_t kMask1, std::uint64_t kMask2, std::uint64_t kFix1, 
          std::uint64_t kFix2, std::uint64_t kPcv1, std::uint64_t kPcv2> inline
void DsfmtEngin<kN, kPosition, kSl, kMask1, kMask2, kFix1, kFix2, kPcv1, kPcv2>::
setSeed(const std::uint32_t seed)
{
  status_[0].u32_[0] = seed;
  initialize();
}

// private member function

/*!
 \details
 No detailed.
 */
template <std::size_t kN, std::size_t kPosition, int kSl,
          std::uint64_t kMask1, std::uint64_t kMask2, std::uint64_t kFix1, 
          std::uint64_t kFix2, std::uint64_t kPcv1, std::uint64_t kPcv2>
void DsfmtEngin<kN, kPosition, kSl, kMask1, kMask2, kFix1, kFix2, kPcv1, kPcv2>::
certificatePeriod()
{
  std::uint64_t tmp[2];
  tmp[0] = status_[kN].u64_[0] ^ kFix1;
  tmp[1] = status_[kN].u64_[1] ^ kFix2;

  std::uint64_t inner = (tmp[0] & kPcv1) ^ (tmp[1] & kPcv2);
  for (int i = 32; i > 0; i >>= 1)
    inner ^= inner >> i;
  inner &= 1;

  // check OK
  if (inner == 1)
    return;

  // check NG, and modification
  if ((kPcv2 & 1) == 1) {
    status_[kN].u64_[1] ^= 1;
  }
  else {
    std::uint64_t pcv[2] = {kPcv1, kPcv2};
    std::uint64_t work;
    for (std::size_t i = 2; i > 0; --i) {
      work = 1;
      for (int j = 0; j < 64; ++j) {
        if ((work & pcv[i - 1]) != 0) {
          status_[kN].u64_[i - 1] ^= work;
          return;
        }
        work = work << 1;
      }
    }
  }
}

/*!
 \details
 No detailed.
 */
template <std::size_t kN, std::size_t kPosition, int kSl,
          std::uint64_t kMask1, std::uint64_t kMask2, std::uint64_t kFix1, 
          std::uint64_t kFix2, std::uint64_t kPcv1, std::uint64_t kPcv2> inline
void DsfmtEngin<kN, kPosition, kSl, kMask1, kMask2, kFix1, kFix2, kPcv1, kPcv2>::
generateRandom(const std::size_t destination, const std::size_t position)
{
  constexpr int kSr = 12;
  const std::uint64_t t0 = status_[destination].u64_[0],
                      t1 = status_[destination].u64_[1],
                      l0 = status_[kN].u64_[0],
                      l1 = status_[kN].u64_[1];
  status_[kN].u64_[0] = 
      (t0 << kSl) ^ (l1 >> 32) ^ (l1 << 32) ^ status_[position].u64_[0];
  status_[kN].u64_[1] = 
      (t1 << kSl) ^ (l0 >> 32) ^ (l0 << 32) ^ status_[position].u64_[1];
  status_[destination].u64_[0] = 
      (status_[kN].u64_[0] >> kSr) ^ (status_[kN].u64_[0] & kMask1) ^ t0;
  status_[destination].u64_[1] = 
      (status_[kN].u64_[1] >> kSr) ^ (status_[kN].u64_[1] & kMask2) ^ t1;
}

/*!
 \details
 No detailed.
 */
template <std::size_t kN, std::size_t kPosition, int kSl,
          std::uint64_t kMask1, std::uint64_t kMask2, std::uint64_t kFix1, 
          std::uint64_t kFix2, std::uint64_t kPcv1, std::uint64_t kPcv2>
void DsfmtEngin<kN, kPosition, kSl, kMask1, kMask2, kFix1, kFix2, kPcv1, kPcv2>::
generateRandomAll()
{
  for (std::size_t i = 0; i < (kN - kPosition); ++i)
    generateRandom(i, i + kPosition);
  for (std::size_t i = (kN - kPosition); i < kN; ++i)
    generateRandom(i, i + kPosition - kN);
}

/*!
 \details
 No detailed.
 */
template <std::size_t kN, std::size_t kPosition, int kSl,
          std::uint64_t kMask1, std::uint64_t kMask2, std::uint64_t kFix1, 
          std::uint64_t kFix2, std::uint64_t kPcv1, std::uint64_t kPcv2>
void DsfmtEngin<kN, kPosition, kSl, kMask1, kMask2, kFix1, kFix2, kPcv1, kPcv2>::
initialize()
{
  constexpr std::uint64_t kHighConst = 0x3ff0000000000000;
  constexpr std::uint64_t kLowMask = 0x000fffffffffffff;

  std::uint32_t* u32_status = &status_[0].u32_[0];

  // Initialize dSFMT engin status.
  for (std::uint32_t i = 1; i < (kN + 1) * 4; ++i)
    u32_status[i] = 1812433253 * (u32_status[i - 1] ^ (u32_status[i - 1] >> 30))+i;

  // Initialize mask
  std::uint64_t* u64_status = &status_[0].u64_[0];
  for (std::size_t i = 0; i < (kN * 2); ++i)
    u64_status[i] = (u64_status[i] & kLowMask) | kHighConst;

  certificatePeriod();
  index_ = kN * 2;
}

} // namespace zisc

#endif // _ZISC_DSFMT_ENGIN_INL_HPP_
