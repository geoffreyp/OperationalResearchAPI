"""The Python implementation of the GRPC helloworld.Greeter client."""

from __future__ import print_function

import grpc

from protoClassClient import api_pb2_grpc
from protoClassClient import api_pb2


def run():
  channel = grpc.insecure_channel('0.0.0.0:50051')
  stub = api_pb2_grpc.OperationalResearchStub(channel)

  print("Init the transaction : ")
  response = stub.InitConversation(api_pb2.InitRequest(customer='Florian', algorithm="hillclimber_first_improvement", solutionSize=5, fitness=100, solution='1-2-3-4-5'))
  print("Client received Id : " + response.id)
  print("Client received Solution : " + response.solution)

  print("Send fitness for the solution received : ")
  response2 = stub.SendFitness(api_pb2.FitnessRequest(id=response.id, fitness=10, solution=response.solution))
  print("Client received Id : " + response2.id)
  print("Client received Solution : " + response2.solution)

  r3 = stub.StopConversation(api_pb2.StopRequest(id=response.id, message="done"))
  print("Client received Id : " + r3.id)
  print("Client received fitness : " + str(r3.fitness))
  print("Client received last Solution : " + r3.solution)

if __name__ == '__main__':
  run()