#include "message_queue.h"
#include "scnet2_monitor.h"

static int scnet2_context_push(uint32_t dst, struct scnet2_msg *msg)
{
    struct scnet2_context *ctx = scnet2_handle_grab(dst);
    if (ctx == NULL) {
        return -1;
    }
    scnet2_mq_push(ctx->queue, msg);
    scnet2_context_release(ctx);

    return 0;
}
int scnet2_send(struct scnet2_context *ctx, uint32_t source, uint32_t dst, 
                int type, int session, void *msg, size_t len)
{
    if (source == 0) {
        source = ctx->handle;
    }

    if (dst == 0) {
        return session;
    }
    if (scnet2_monitor_isremote_msg(dst)) {
        struct remote_msg *rmsg = malloc(sizeof(*rmsg));
        rmsg->dst.handle = dst;
        rmsg->msg = msg;
        rmsg->sz = len;
        
        scnet2_monitor_send(rmsg, source, session);
    } else { /* local msg*/
        struct scnet2_msg msg;
        msg.source = source;
        msg.session = session;
        msg.msg = msg;
        msg.sz = len;

        if(scnet2_context_push(dst, &msg)) {
            free(msg);
            /*ERROR handle here*/
            return -1;
        }
    }

    return session;
}

int scnet2_context_send(struct scnet2_context *ctx, void *msg, size_t sz, uint32_t source,
                       int type, int session)
{
    struct scnet2_msg msg;
    msg.source = source;
    msg.session = session;
    msg.data = msg;
    msg.sz = sz | type  << HANDLER_REMOTE_SHIFT;

    scnet2_mq_push(ctx->queue, &msg);
}
