/**************************************************************************************************/
/**
 * \brief RIFF tests
 */
/**************************************************************************************************/

#include <gtest/gtest.h>
#include <stdlib.h>
#include <string>

extern "C" {
#include "riff.h"
}

using namespace std;

/**************************************************************************************************/

TEST(CreateSubChunk, CleanSubchunkOK)
{
    riffSubChunk_t subchunk;

    subchunk = riffSubChunkCreate("TEST");
    ASSERT_EQ(string(subchunk.id), "TEST");
    ASSERT_NE(string(subchunk.id), "TSET");
    ASSERT_EQ(subchunk.size, 0);
    ASSERT_EQ(subchunk.payload, (void *) NULL);
}

/**************************************************************************************************/
/**************************************************************************************************/

TEST(CreateChunk, EmptyChunkOK)
{
    riffChunk_t chunk;

    /* Create an empty RIFF chunk and check its parameters */
    chunk = riffChunkCreate();
    ASSERT_EQ(chunk.size, RIFF_FORMAT_TYPE_LEN);
    ASSERT_EQ(chunk.formatType, RIFF_FMT_TYPE_UNKNOWN);
    ASSERT_EQ(chunk.numOfSubchunks, 0);
    ASSERT_EQ(chunk.subChunks, (riffSubChunk_t **) NULL);
}

/**************************************************************************************************/

TEST(CreateChunk, ChunkWithTypeOK)
{
    riffChunk_t chunk;

    /* Create empty RIFF chunks with all format types and check the parameters */
    for (int i = RIFF_FMT_TYPE_UNKNOWN + 1; i < RIFF_FMT_TYPE_LAST; i++) {
        ASSERT_EQ(riffChunkCreateWithType(&chunk, (riffFormatType_t)i), RIFF_ERR_NONE);
        ASSERT_EQ(chunk.size, RIFF_FORMAT_TYPE_LEN);
        ASSERT_EQ(chunk.formatType, i);
        ASSERT_EQ(chunk.numOfSubchunks, 0);
        ASSERT_EQ(chunk.subChunks, (riffSubChunk_t **) NULL);
    }
}

/**************************************************************************************************/

TEST(CreateChunk, ChunkWithInvalidTypesERRE)
{
    riffChunk_t chunk;
    riffSubChunk_t **nullPointer = NULL;

    ASSERT_EQ(riffChunkCreateWithType(&chunk, RIFF_FMT_TYPE_UNKNOWN), RIFF_ERR_PARAM_OUT_OF_RANGE);
    ASSERT_EQ(riffChunkCreateWithType(&chunk, RIFF_FMT_TYPE_LAST), RIFF_ERR_PARAM_OUT_OF_RANGE);
    ASSERT_EQ(riffChunkCreateWithType(&chunk, (riffFormatType_t)-1), RIFF_ERR_PARAM_OUT_OF_RANGE);
}

/**************************************************************************************************/
