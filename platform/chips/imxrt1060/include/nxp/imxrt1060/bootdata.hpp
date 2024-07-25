#pragma once
#import "cinttypes"
#import "cstddef"

namespace nxp::imxrt1060 {
	/** Boot Data
	 * - IMXRT1060RM_rev1_Processor_Manual.pdf: 8.7.1.2
	 */
	struct boot_data_t {
		const void*    start;
		const size_t   length;
		const uint32_t plugin;
	};

	static_assert(sizeof(nxp::imxrt1060::boot_data_t) == 12, "Boot Data must be 12 bytes long.");
} // namespace nxp::imxrt1060
