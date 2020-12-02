/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ES8P508_IAP_TABLE_H
#define __ES8P508_IAP_TABLE_H

#ifdef __cplusplus
extern "C" {
#endif

	/* Includes ------------------------------------------------------------------*/
#include "ES8P508x.h"
#include "type.h"

	/** @addtogroup ES8P508x.h_HrPeriph_Driver
	 * @{
	 */

	/** @addtogroup IAP_TABLE
	 * @{
	 */

	/** @defgroup IAP_TABLE_Exported_Types
	 * @{
	 */


	/**
	 * @}
	 */

	/** @defgroup IAP_TABLE_Exported_Constants
	 * @{
	 */


	/** @defgroup IAP_TABLE_ADDR
	 * @{
	 */

#define IAP_PageProgram_addr	0x10000000
#define IAP_PageErase_addr		0x10000004
#define IAP_WordProgram_addr	0x10000008

	//回调函数定义
	typedef ErrorStatus (*IAP_PE)(uint32_t address);    
	typedef ErrorStatus (*IAP_WP)(uint32_t address, uint32_t data);
	typedef ErrorStatus (*IAP_PP)(uint32_t address, uint32_t data[], uint32_t length, uint32_t erase);

	//函数声明
	ErrorStatus IAP_PageErase(uint32_t address);
	ErrorStatus IAP_WordProgram(uint32_t address, uint32_t data);
	ErrorStatus IAP_PageProgram(uint32_t address, uint32_t data[], uint32_t length, uint32_t erase);
	ErrorStatus IAPRead(uint32_t *Ram_Addr, uint32_t Flash_Addr, uint8_t Len);
	/** @defgroup IAP_PageProgram erase
	 * @{
	 */

#define PageEraseEnable				0x00000001
#define PageEraseDisable			0x00000000

	/**
	 * @}
	 */


	/** @defgroup typedef 
	 * @{
	 */

	//typedef void (* pfunc_erase)(uint32_t);
	//typedef void (* pfunc_word)(uint32_t, uint32_t);
	//typedef void (* pfunc_page)(uint32_t, unsigned char *, uint32_t, uint32_t);

	/**
	 * @}
	 */

	/**
	 * @}
	 */

	/** @defgroup IAP_TABLE_Exported_Macros
	 * @{
	 */

	/**
	 * @}
	 */

	/** @defgroup IAP_TABLE_Exported_Functions
	 * @{
	 */
	//__ASM ErrorStatus IAP_PageErase(uint32_t address);
	//__ASM ErrorStatus IAP_WordProgram(uint32_t address, uint32_t data);
	//__ASM ErrorStatus IAP_PageProgram(uint32_t address, uint32_t data[], uint32_t length, uint32_t erase);

#ifdef __cplusplus
}
#endif

#endif /*ES8P508x_IAP_TABLE_H */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/******************* (C) COPYRIGHT 2014 ICHaier *****END OF FILE****/
