#pragma once

#include <cstdint>

namespace Jupiter::Io {

	struct LoadedAsset {
		uint32_t m_FileInputType = 0;
		void* m_Source;
	};

}
