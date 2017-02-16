/**************************************************************************************************/
/**
 * \brief  RIFF library file
 */
/**************************************************************************************************/

#include <string.h>
#include <stdlib.h>
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
    int i;
    riffSubChunk_t *subCkunksBkp[chunk->numOfSubchunks];

    /* Backup subchunks */
    for (i = 0; i < chunk->numOfSubchunks; i++) {
        subCkunksBkp[i] = chunk->subChunks[i];
    }

    /* Delete allocation for the subchunks pointers */
    free(chunk->subChunks);

    /* Reallocate memory for the new size */
    chunk->subChunks = (riffSubChunk_t**) malloc((chunk->numOfSubchunks + 1) * sizeof(riffChunk_t));

    /* Copy back the old subchunks */
    for(i = 0; i < chunk->numOfSubchunks; i++) {
        chunk->subChunks[i] = subCkunksBkp[i];
    }

    /* Allocate and save the new subchunk */
    chunk->subChunks[i] = (riffSubChunk_t*) malloc(sizeof(riffSubChunk_t));
    memcpy(chunk->subChunks[i], &subChunk, sizeof(riffSubChunk_t));

    return RIFF_ERR_NONE;
}

/**************************************************************************************************/
