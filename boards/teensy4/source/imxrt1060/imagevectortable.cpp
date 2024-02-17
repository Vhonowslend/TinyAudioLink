#include "imagevectortable.hpp"

[[gnu::used, gnu::section(".imageVectorTable")]] imxrt1060::image_vector_table_t imxrt1060::__image_vector_table = {
	//	.entryPoint = &_start,
	.bootData = &__boot_data,
	.self     = &__image_vector_table,
};
