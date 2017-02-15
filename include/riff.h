/**************************************************************************************************/
/**
 * \brief  RIFF library file
 */
/**************************************************************************************************/

#ifndef __LIB_RIFF_RIFF_H__
#define __LIB_RIFF_RIFF_H__

#include <stdint.h>
#include <stddef.h>

/**************************************************************************************************/

#define RIFF_FORMAT_TYPE_LEN 4  //!< RIFF format type length in bytes

/**************************************************************************************************/

/**
 * \brief  RIFF error codes
 */
typedef enum {
    RIFF_ERR_NONE = 0,
} riffError_t;

/**
 * \brief  RIFF payload format type definition
 */
typedef enum {
    RIFF_FMT_TYPE_UNKNOWN,
    RIFF_FMT_TYPE_CPPO,
    RIFF_FMT_TYPE_PAL,
    RIFF_FMT_TYPE_RDIB,
    RIFF_FMT_TYPE_RMID,
    RIFF_FMT_TYPE_RMMP,
    RIFF_FMT_TYPE_WAVE,
} riffFormatType_t;

/**
 * \biref  RIFF Subchunk generic structure description
 */
typedef struct {
    char id[4];    //!< ASCII ID
    uint32_t size; //!< Payload total size
    void *payload; //!< Pointer to payload
} riffSubChunk_t;

/**
 * \brief  RUFF main chunk structure description
 */
typedef struct {
    // The RIFF ID is omitted because it's fixed as "RIFF", where 'R' is the
    // LSByte
    uint32_t size;               //!< Payload total size (in bytes) including format type
    riffFormatType_t formatType; //!< Type of RIFF
    uint32_t numOfSubchunks;     //!< Number of subchunks in array
    riffSubChunk_t **subChunks;  //!< Array containing pointers to the subchunks
} riffChunk_t;

/**************************************************************************************************/

/**
 * \brief  Create an empty RIFF chunk
 * \return Created RIFF chunk
 */
riffChunk_t riffChunkCreate();

/**
 * \brief  Add a subchunk into a RIFF chunk
 * \param  chunk     (out) Pointer to have the subchunk added
 * \param subChunks  (in)  Subchunk to be added
 * \return RIFF_ERR_NONE on success, error code otherwise
 */
riffError_t riffAddSubchunk(riffChunk_t *chunk, riffSubChunk_t subChunk);

/**************************************************************************************************/

#endif /* __LIB_RIFF_RIFF_H__ */

/**************************************************************************************************/
