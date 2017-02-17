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

TEST(Subchunk, CreateCleanSubchunkOK)
{
    riffSubChunk_t subchunk;

    subchunk = riffSubChunkCreate("TEST");
    ASSERT_EQ(string(subchunk.id), "TEST");
    ASSERT_NE(string(subchunk.id), "TSET");
    ASSERT_EQ(subchunk.size, 0);
    ASSERT_EQ(subchunk.payload, (void *) NULL);
}

/**************************************************************************************************/

TEST(Subchunk, SetPayloadInvalidPayloadERROR)
{
    riffSubChunk_t subchunk;
    subchunk = riffSubChunkCreate("TEST");

    ASSERT_EQ(riffSubchunkSetPayload(&subchunk, NULL, sizeof(int)), RIFF_ERR_INVALID_PARAM);
}

/**************************************************************************************************/

TEST(Subchunk, SetPayloadInvalidSubchunkERROR)
{
    int payload = 5;
    ASSERT_EQ(riffSubchunkSetPayload(NULL, &payload, sizeof(payload)), RIFF_ERR_INVALID_PARAM);
}

/**************************************************************************************************/

TEST(Subchunk, SetPayloadFirstTimeOK)
{
    riffSubChunk_t subchunk;
    int payload[3];

    subchunk = riffSubChunkCreate("TEST");
    payload[0] = 5;
    payload[1] = 6;
    payload[2] = 7;

    ASSERT_EQ(riffSubchunkSetPayload(&subchunk, &payload, sizeof(payload)), RIFF_ERR_NONE);

    ASSERT_EQ(subchunk.size, sizeof(int) * 3);
    ASSERT_EQ(payload[0], ((int *)(subchunk.payload))[0]);
    ASSERT_EQ(payload[1], ((int *)(subchunk.payload))[1]);
    ASSERT_EQ(payload[2], ((int *)(subchunk.payload))[2]);
}

/**************************************************************************************************/

TEST(Subchunk, SetPayloadOverrideTimeOK)
{
    riffSubChunk_t subchunk;
    int payload1[3];
    int payload2[5];

    subchunk = riffSubChunkCreate("TEST");
    payload1[0] = 5;
    payload1[1] = 6;
    payload1[2] = 7;
    payload2[0] = 8;
    payload2[1] = 9;
    payload2[2] = 10;
    payload2[3] = 11;
    payload2[4] = 12;

    ASSERT_EQ(riffSubchunkSetPayload(&subchunk, &payload1, sizeof(payload1)), RIFF_ERR_NONE);
    ASSERT_EQ(riffSubchunkSetPayload(&subchunk, &payload2, sizeof(payload2)), RIFF_ERR_NONE);

    ASSERT_EQ(subchunk.size, sizeof(int) * 5);
    ASSERT_EQ(payload2[0], ((int *)(subchunk.payload))[0]);
    ASSERT_EQ(payload2[1], ((int *)(subchunk.payload))[1]);
    ASSERT_EQ(payload2[2], ((int *)(subchunk.payload))[2]);
    ASSERT_EQ(payload2[3], ((int *)(subchunk.payload))[3]);
    ASSERT_EQ(payload2[4], ((int *)(subchunk.payload))[4]);
}

/**************************************************************************************************/
/**************************************************************************************************/

TEST(Chunk, CreateEmptyChunkOK)
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

TEST(Chunk, CreateChunkWithTypeOK)
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

TEST(Chunk, CreateChunkWithInvalidTypesERROR)
{
    riffChunk_t chunk;
    riffSubChunk_t **nullPointer = NULL;

    ASSERT_EQ(riffChunkCreateWithType(&chunk, RIFF_FMT_TYPE_UNKNOWN), RIFF_ERR_PARAM_OUT_OF_RANGE);
    ASSERT_EQ(riffChunkCreateWithType(&chunk, RIFF_FMT_TYPE_LAST), RIFF_ERR_PARAM_OUT_OF_RANGE);
    ASSERT_EQ(riffChunkCreateWithType(&chunk, (riffFormatType_t)-1), RIFF_ERR_PARAM_OUT_OF_RANGE);
}

/**************************************************************************************************/

TEST(Chunk, AddOneSubchunkOK)
{
    riffChunk_t chunk;
    ASSERT_EQ(riffChunkCreateWithType(&chunk, RIFF_FMT_TYPE_WAVE), RIFF_ERR_NONE);

    /* Create the subchunk */
    riffSubChunk_t subchunk;
    subchunk = riffSubChunkCreate("TEST");
    int payload[3];
    payload[0] = 5;
    payload[1] = 6;
    payload[2] = 7;
    ASSERT_EQ(riffSubchunkSetPayload(&subchunk, &payload, sizeof(payload)), RIFF_ERR_NONE);

    /* Add the subchunk into the chunk */
    ASSERT_EQ(riffAddSubchunk(&chunk, subchunk), RIFF_ERR_NONE);
}

/**************************************************************************************************/
