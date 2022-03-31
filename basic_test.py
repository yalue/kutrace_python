# This script should return with no errors and produce basic_test.trace. You
# can use the KUtrace postprocessing tools to transform this into
# basic_test.html, which should display four markers from the python process.
import sys
import kutrace
import random

def spin(v):
    """ Just wastes a bit of time. """
    to_return = 0.0
    for i in range(v):
        to_return += random.random()
    return to_return

assert(kutrace.test())
kutrace.goipc("python")
kutrace.mark_a("mark-a")
spin(10000)
kutrace.mark_b("mark-b")
spin(5000)
kutrace.mark_c("mark-c")
spin(1000)
kutrace.mark_d(1337)
kutrace.stop("basic_test.trace")

