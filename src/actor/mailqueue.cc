struct message_queue {
  uint32_t handle;
  int capcity;
  int head;
  int tail;
  int lock;
  int release;
  int lock_session;
  int in_global;
  struct scnet2_message *queue;
};

struct global_queue {
  uint32_t head;
  uint32_t tail;
  struct message_queue **queue;
  bool *flag;
}

struct message_queue *scnet2_mq_create(uint32_t handle) {
  struct message_queue *q = malloc(sizeof(*q));
  q->handle = handle;
  q->capcity = DEFAULT_MQ_SIZE;
  q->head = 0;
  q->tail = 0;
  q->lock = 0;
  q->in_global = MQ_GLOBAL;
  q->release = 0;
  q->lock_session = 0;
  q->queue = malloc(sizeof(struct scnet2_message) * q->capcity);

  return q;
}

void scnet2_mq_push(struct message_queue *q, struct local_msg *msg)
{
  MutextLock lock;
  {
    MutexLockGuard guard(lock);
    if (q->lock_session != 0 && msg->session == q->lock_session) {
      pushhead(q, msg);
    } else {
      q->queue[q->tail] = *msg;
      if (++q->tail >= q->cap) {
        q->tail = 0;
      }

      if (q->head == q->tail) {
        expand_queue(q);
      }

      if (q->lock_session == 0) {
        if (q->in_global == 0) {
          q->in_global = MQ_GLOBAL;
          scnet2_globalmq_push(q);
        }
      }
    }

  }

}

static struct global_queue *Q = NULL;
void scnet2_globalmq_push(struct message_queue *queue)
{
  strcut global_queue *q = Q;

  uint32_t tmp = __sync_fetch_and_add(&q->tail, 1);
  uint32_t tail = tmp % MAX_GLOBAL_MQ;
  q->queue[tail] = queue;
  __sync_synchronize();
  // flag the tail index has queue
  q->flag[tail] = true;
  __sync_synchronize();
}
