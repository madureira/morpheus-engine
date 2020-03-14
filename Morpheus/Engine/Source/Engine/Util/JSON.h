#pragma once

#include <nlohmann/json.hpp>
#include <nlohmann/fifo_map.hpp>

namespace Morpheus {

	template<class K, class V, class dummy_compare, class A>
	using json_fifo_map = nlohmann::fifo_map<K, V, nlohmann::fifo_map_compare<K>, A>;
	using JSON = nlohmann::basic_json<json_fifo_map>;

}
