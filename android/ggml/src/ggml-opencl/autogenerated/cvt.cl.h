R"(//------------------------------------------------------------------------------
)"
R"(// This file is contains kernels for data conversion.
)"
R"(// These kernels are used when loading the model, so its performance is less
)"
R"(// important.
)"
R"(//------------------------------------------------------------------------------
)"
R"(#pragma OPENCL EXTENSION cl_khr_fp16 : enable
)"
R"(
)"
R"(#ifdef cl_intel_required_subgroup_size
)"
R"(#pragma OPENCL EXTENSION cl_intel_required_subgroup_size : enable
)"
R"(#define INTEL_GPU 1
)"
R"(#define REQD_SUBGROUP_SIZE_16 __attribute__((intel_reqd_sub_group_size(16)))
)"
R"(#define REQD_SUBGROUP_SIZE_32 __attribute__((intel_reqd_sub_group_size(32)))
)"
R"(#elif defined(cl_qcom_reqd_sub_group_size)
)"
R"(#pragma OPENCL EXTENSION cl_qcom_reqd_sub_group_size : enable
)"
R"(#define ADRENO_GPU 1
)"
R"(#define REQD_SUBGROUP_SIZE_64  __attribute__((qcom_reqd_sub_group_size("half")))
)"
R"(#define REQD_SUBGROUP_SIZE_128 __attribute__((qcom_reqd_sub_group_size("full")))
)"
R"(#endif
)"
R"(
)"
R"(#define QK4_0                   32
)"
R"(#define QR4_0                   2
)"
R"(#define QK4_1                   32
)"
R"(#define QR4_1                   2
)"
R"(#define QK5_0                   32
)"
R"(#define QR5_0                   2
)"
R"(#define QK5_1                   32
)"
R"(#define QR5_1                   2
)"
R"(#define QK8_0                   32
)"
R"(#define QR8_0                   1
)"
R"(#define QK_K                    256
)"
R"(#define K_QUANTS_PER_ITERATION  2
)"
R"(
)"
R"(typedef char int8_t;
)"
R"(typedef uchar uint8_t;
)"
R"(typedef short int16_t;
)"
R"(typedef ushort uint16_t;
)"
R"(typedef int int32_t;
)"
R"(typedef uint uint32_t;
)"
R"(
)"
R"(//------------------------------------------------------------------------------
)"
R"(// block_q4_0
)"
R"(//------------------------------------------------------------------------------
)"
R"(struct block_q4_0
)"
R"({
)"
R"(    half d;
)"
R"(    uint8_t qs[QK4_0 / 2];
)"
R"(};
)"
R"(
)"
R"(//------------------------------------------------------------------------------
)"
R"(// kernel_convert_block_q4_0
)"
R"(// Convert the block_q4_0 format to 2 separate arrays (AOS -> SOA).
)"
R"(// This kernel does not deshuffle the bits.
)"
R"(//------------------------------------------------------------------------------
)"
R"(kernel void kernel_convert_block_q4_0(
)"
R"(    global struct block_q4_0 * src0,
)"
R"(    global uchar * dst_q,
)"
R"(    global half  * dst_d
)"
R"() {
)"
R"(    global struct block_q4_0 * b = (global struct block_q4_0 *) src0 + get_global_id(0);
)"
R"(    global uchar * q = (global uchar *) dst_q + QK4_0/2*get_global_id(0);
)"
R"(    global half  * d = (global half *) dst_d + get_global_id(0);
)"
R"(
)"
R"(    *d = b->d;
)"
R"(
)"
R"(    for (int i = 0; i < QK4_0/2; ++i) {
)"
R"(        q[i] = b->qs[i];
)"
R"(    }
)"
R"(}
)"
R"(
)"
R"(kernel void kernel_restore_block_q4_0(
)"
R"(    global uchar * src_q,
)"
R"(    global half  * src_d,
)"
R"(    global struct block_q4_0 * dst
)"
R"() {
)"
R"(    global struct block_q4_0 * b = (global struct block_q4_0 *) dst + get_global_id(0);
)"
R"(    global uchar * q = (global uchar *) src_q + QK4_0/2*get_global_id(0);
)"
R"(    global half  * d = (global half *) src_d + get_global_id(0);
)"
R"(
)"
R"(    b->d = *d;
)"
R"(    for (int i = 0; i < QK4_0/2; ++i) {
)"
R"(        b->qs[i] = q[i];
)"
R"(    }
)"
R"(}
)"
R"(
)"
R"(//------------------------------------------------------------------------------
)"
R"(// kernel_convert_block_q4_0_noshuffle
)"
R"(// Flatten q4_0 weights and unshuffle the bits
)"
R"(//------------------------------------------------------------------------------
)"
R"(
)"
R"(kernel void kernel_convert_block_q4_0_noshuffle(
)"
R"(    global struct block_q4_0 * src0,
)"
R"(    global uchar * dst_q,
)"
R"(    global half  * dst_d
)"
R"() {
)"
R"(    global struct block_q4_0 * b = (global struct block_q4_0 *) src0 + get_global_id(0);
)"
R"(    global uchar * q = (global uchar *) dst_q + QK4_0/2*get_global_id(0);
)"
R"(    global half  * d = (global half *) dst_d + get_global_id(0);
)"
R"(
)"
R"(    *d = b->d;
)"
R"(    for (int i = 0; i < QK4_0/4; ++i) {
)"
R"(        uchar x0 = b->qs[2*i + 0];
)"
R"(        uchar x1 = b->qs[2*i + 1];
)"
R"(
)"
R"(        q[i + 0      ] = convert_uchar(x0 & 0x0F) | convert_uchar((x1 & 0x0F) << 4);
)"
R"(        q[i + QK4_0/4] = convert_uchar((x0 & 0xF0) >> 4) | convert_uchar(x1 & 0xF0);
)"
R"(
)"
R"(#ifdef ADRENO_GPU
)"
R"(        // Workaround for adreno - must have the following printf statement for
)"
R"(        // the kernel to work properly. Otherwise it produces incorrect result.
)"
R"(        // convert_uchar above also seems necessary.
)"
R"(        // Compare against a large number so that it does not print anything.
)"
R"(        // get_sub_group_local_id() also works.
)"
R"(        if (get_global_id(0) == 65536*4096) {
)"
R"(            printf("%04x - %02x\n", *(global ushort*)d, ((x0 & 0xF0) >> 4) | (x1 & 0xF0));
)"
R"(        }
)"
R"(#endif
)"
R"(    }
)"
R"(}
)"
