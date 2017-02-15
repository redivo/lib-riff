/**************************************************************************************************/
/**
 * \brief  RIFF library file
 */
/**************************************************************************************************/

#include "riff.h"

/**************************************************************************************************/

riffChunk_t riffChunkCreate()
{
    riffChunk_t chunk;

    /* The initial size of RIFF chunk include only size of format type */
    chunk.size = RIFF_FORMAT_TYPE_LEN;
    chunk.formatType = RIFF_FMT_TYPE_UNKNOWN;
    chunk.numOfSubchunks = 0;
    chunk.subChunks = NULL;

    return chunk;
}

/**************************************************************************************************/

riffError_t riffAddSubchunk(riffChunk_t *chunk, riffSubChunk_t subChunk)
{
    riffSubChunk_t * ???

    return RIFF_ERR_NONE;
}


/**************************************************************************************************/
