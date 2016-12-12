#include "MoveConventer.h"

//std::string ConvertToString(std::pair<sf::Vector2i, sf::Vector2i> _pair)
//{
//	int coordinations[4] = { 0 };
//	coordinations[0] = _pair.first.x;
//	coordinations[1] = _pair.first.y;
//	coordinations[2] = _pair.second.x;
//	coordinations[3] = _pair.second.y;
//	
//	std::string move = "";
//
//	for (size_t i = 0; i < 4; i++)
//	{
//		switch (coordinations[i])
//		{
//			case 0:
//			{
//				if (i % 2 == 0)
//				{
//					move += 'A';
//				}
//				else
//				{
//					move += 8;
//				}
//				break;
//			}
//			case 1:
//			{
//				if (i % 2 == 0)
//				{
//					move += 'B';
//				}
//				else
//				{
//					move += 7;
//				}
//				break;
//			}
//			case 2:
//			{
//				if (i % 2 == 0)
//				{
//					move += 'C';
//				}
//				else
//				{
//					move += 6;
//				}
//				break;
//			}
//			case 3:
//			{
//				if (i % 2 == 0)
//				{
//					move += 'D';
//				}
//				else
//				{
//					move += 5;
//				}
//				break;
//			}
//			case 4:
//			{
//				if (i % 2 == 0)
//				{
//					move += 'E';
//				}
//				else
//				{
//					move += 4;
//				}
//				break;
//			}
//			case 5:
//			{
//				if (i % 2 == 0)
//				{
//					move += 'F';
//				}
//				else
//				{
//					move += 3;
//				}
//				break;
//			}
//			case 6:
//			{
//				if (i % 2 == 0)
//				{
//					move += 'G';
//				}
//				else
//				{
//					move += 2;
//				}
//				break;
//			}
//			case 7:
//			{
//				if (i % 2 == 0)
//				{
//					move += 'H';
//				}
//				else
//				{
//					move += 1;
//				}
//				break;
//			} 
//		default:
//			break;
//		}
//	}
//
//	return move;
//}
//
//std::pair<sf::Vector2i, sf::Vector2i> ConvertToVec(std::string _move)
//{
//	int startX, startY, endX, endY;
//	
//	for (size_t i = 0; i < 4; i++)
//	{	
//		
//		if(_move.at(i) == 'A')
//		{
//			if (i < 2)
//			{
//				startX = 0;
//			}
//			else
//			{
//				endX = 0;
//			}
//			break;
//		}
//		else if (_move.at(i) == 'B')
//		{
//			if (i < 2)
//			{
//				startX = 1;
//			}
//			else
//			{
//				endX = 1;
//			}		
//			break;
//		}
//		else if (_move.at(i) == 'C')
//		{
//			if (i < 2)
//			{
//				startX = 2;
//			}
//			else
//			{
//				endX = 2;
//			}
//			break;
//		}
//		else if (_move.at(i) == 'D')
//		{
//			if (i < 2)
//			{
//				startX = 3;
//			}
//			else
//			{
//				endX = 3;
//			}
//			break;
//		}
//		else if (_move.at(i) == 'E')
//		{
//			if (i < 2)
//			{
//				startX = 4;
//			}
//			else
//			{
//				endX = 4;
//			}
//			break;
//		}
//		else if (_move.at(i) == 'F')
//		{
//			if (i < 2)
//			{
//				startX = 5;
//			}
//			else
//			{
//				endX = 5;
//			}
//			break;
//		}
//		else if (_move.at(i) == 'G')
//		{
//			if (i < 2)
//			{
//				startX = 6;
//			}
//			else
//			{
//				endX = 6;
//			}
//			break;
//		}
//		else if (_move.at(i) == 'H')
//		{
//			if (i < 2)
//			{
//				startX = 7;
//			}
//			else
//			{
//				endX = 7;
//			}
//			break;
//		}
//		else if (_move.at(i) == '1')
//		{
//			if (i < 2)
//			{
//				startY = 0;
//			}
//			else
//			{
//				endY = 0;
//			}
//			break;
//			break;
//		}
//		else if (_move.at(i) == '2')
//		{
//			if (i < 2)
//			{
//				startY = 1;
//			}
//			else
//			{
//				endY = 1;
//			}
//			break;
//		}
//		else if (_move.at(i) == '3')
//		{
//			if (i < 2)
//			{
//				startY = 2;
//			}
//			else
//			{
//				endY = 2;
//			}
//			break;
//		}
//		else if (_move.at(i) == '4')
//		{
//			if (i < 2)
//			{
//				startY = 3;
//			}
//			else
//			{
//				endY = 3;
//			}
//			break;
//		}
//		else if (_move.at(i) == '5')
//		{
//			if (i < 2)
//			{
//				startY = 4;
//			}
//			else
//			{
//				endY = 4;
//			}
//			break;
//		}
//		else if (_move.at(i) == '6')
//		{
//			if (i < 2)
//			{
//				startY = 5;
//			}
//			else
//			{
//				endY = 5;
//			}
//			break;
//		}
//		else if (_move.at(i) == '7')
//		{
//			if (i < 2)
//			{
//				startY = 6;
//			}
//			else
//			{
//				endY = 6;
//			}
//			break;
//		}
//		else if (_move.at(i) == '8')
//		{
//			if (i < 2)
//			{
//				startY = 7;
//			}
//			else
//			{
//				endY = 7;
//			}
//			break;
//		}
//	}
//	
//	return std::make_pair(sf::Vector2i(startX, startY), sf::Vector2i(endX, endY));
//}
//
//std::pair<sf::Vector2i, sf::Vector2i> ConvertIntIntoPair(int _toBeConverter)
//{
//	_toBeConverter = ~_toBeConverter;
//
//	char move[4];
//	move[0] = (_toBeConverter >> 24);
//	move[1] = (_toBeConverter >> 16);
//	move[2] = (_toBeConverter >> 8);
//	move[3] = (_toBeConverter >> 0);
//
//	/*std::string unpackedMove = "";
//	unpackedMove.append(move);*/
//
//	sf::Vector2i startingPosition = sf::Vector2i(move[0], move[1]);
//	sf::Vector2i endPosition = sf::Vector2i(move[2], move[3]);
//	return std::make_pair(startingPosition, endPosition);
//}