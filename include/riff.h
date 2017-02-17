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
    RIFF_ERR_GENERIC = -1,
    RIFF_ERR_PARAM_OUT_OF_RANGE = -2,
    RIFF_ERR_INVALID_PARAM = -3,
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

    RIFF_FMT_TYPE_LAST
} riffFormatType_t;

/**************************************************************************************************/
/* RIFF subchunk                                                                                  */
/**************************************************************************************************/

#define RIFF_SUBCHUNK_ID_LEN 4

/**
 * \biref  RIFF Subchunk generic structure description
 */
typedef struct {
    char id[RIFF_SUBCHUNK_ID_LEN]; //!< ASCII ID
    uint32_t size;                 //!< Payload total size
    void *payload;                 //!< Pointer to payload
} riffSubChunk_t;

/**
 * \brief  Create a RIFF subchunk with an specific ID
 * \param  id  ID of the RIFF subchunk that will be created
 * \return Created RIFF subchunk
 */
riffSubChunk_t riffSubChunkCreate(const char id[RIFF_SUBCHUNK_ID_LEN]);

/**
 * \biref  Set the payload (copying content) into subchunk. If it's already set, override it
 * \param  subchunk  (out) Subchunk to be filled
 * \param  payload   (in)  Pointer to data to be stored
 * \param  size      (in)  Size, in bytes, to be copied from 'payload'
 * \return RIFF_ERR_NONE on success, error code otherwise
 */
riffFormatType_t riffSubchunkSetPayload(riffSubChunk_t *subchunk, void *payload, size_t size);

/**************************************************************************************************/
/* RIFF chunk                                                                                     */
/**************************************************************************************************/

/**
 * \brief  RIFF main chunk structure description
 */
typedef struct {
    // The RIFF ID is omitted because it's fixed as "RIFF", where 'R' is the
    // LSByte
    uint32_t size;               //!< Payload total size (in bytes) including format type
    riffFormatType_t formatType; //!< Type of RIFF
    uint32_t numOfSubchunks;     //!< Number of subchunks in array
    riffSubChunk_t **subChunks;  //!< Array containing pointers to the subchunks
} riffChunk_t;

/**
 * \brief  Create an empty RIFF chunk
 * \return Created RIFF chunk
 */
riffChunk_t riffChunkCreate();

/**
 * \brief  Create a RIFF chunk with an specific type
 * \param  chunk  (out) Pointer to the RIFF chunk to be filled
 * \param  type   (in)  Type of the RIFF chunk that will be created
 * \return RIFF_ERR_NONE on success, error code otherwise
 */
riffError_t riffChunkCreateWithType(riffChunk_t *chunk, riffFormatType_t type);

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
