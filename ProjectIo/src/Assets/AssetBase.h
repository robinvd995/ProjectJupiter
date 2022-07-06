#pragma once

namespace Jupiter::Io {

	class AssetBase {

	public:
		AssetBase() {}
		~AssetBase() {}

		virtual size_t getAssetSize() = 0;
		virtual char* getAssetSource() = 0;

	};

}