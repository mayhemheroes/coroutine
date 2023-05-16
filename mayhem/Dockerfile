# Build Stage:
FROM --platform=linux/amd64 ubuntu:20.04 as builder

## Install build dependencies.
RUN apt update && \
    DEBIAN_FRONTEND=noninteractive apt install -y clang --no-install-recommends

## Add Source Code
ADD *.c /
ADD *.h /

## Build Step
RUN clang -fsanitize=fuzzer -o coroutine_fuzzable fuzzable.c coroutine.c

# Package Stage
FROM --platform=linux/amd64 ubuntu:20.04
COPY --from=builder /coroutine_fuzzable /
