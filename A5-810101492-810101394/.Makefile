CC_EXEC=g++
CC_FLAGS =-g

CC=${CC_EXEC} ${CC_FLAGS}

BUILD_DIR=bin

all: a.out

a.out:
	g++ ${BUILD_DIR}/main.o  ${BUILD_DIR}/animation.o ${BUILD_DIR}/BonusEntity.o ${BUILD_DIR}/collision.o ${BUILD_DIR}/EnemyEntity.o ${BUILD_DIR}/game.o ${BUILD_DIR}/GameEntity.o ${BUILD_DIR}/LiveEntity.o ${BUILD_DIR}/MadEnemy.o ${BUILD_DIR}/MiniTurtle.o ${BUILD_DIR}/platform.o ${BUILD_DIR}/read_map.o ${BUILD_DIR}/text.o ${BUILD_DIR}/turtix.o -lsfml-window -lsfml-graphics -lsfml-system -o ${BUILD_DIR}/a.out

${BUILD_DIR}/main.o: main.cpp game.h
	${CC} -c main.cpp -o ${BUILD_DIR}/main.o
 
${BUILD_DIR}/animation.o: animation.cpp animation.h
	${CC} -c animation.cpp -o ${BUILD_DIR}/animation.o
	
${BUILD_DIR}/BonusEntity.o: BonusEntity.cpp BonusEntity.h GameEntity.h
	${CC} -c BonusEntity.cpp -o ${BUILD_DIR}/BonusEntity.o

${BUILD_DIR}/collision.o: collision.cpp collision.h turtix.h
	${CC} -c collision.cpp -o ${BUILD_DIR}/collision.o

${BUILD_DIR}/EnemyEntity.o: EnemyEntity.cpp EnemyEntity.h turtix.h
	${CC} -c EnemyEntity.cpp -o ${BUILD_DIR}/EnemyEntity.o

${BUILD_DIR}/game.o: game.cpp game.h read_map.h collision.h MiniTurtle.h BonusEntity.h text.h MadEnemy.h
	${CC} -c game.cpp -o ${BUILD_DIR}/game.o

${BUILD_DIR}/GameEntity.o: GameEntity.cpp GameEntity.h animation.h platform.h
	${CC} -c GameEntity.cpp -o ${BUILD_DIR}/GameEntity.o

${BUILD_DIR}/LiveEntity.o: LiveEntity.cpp LiveEntity.h GameEntity.h
	${CC} -c LiveEntity.cpp -o ${BUILD_DIR}/LiveEntity.o

${BUILD_DIR}/MadEnemy.o: MadEnemy.cpp MadEnemy.h EnemyEntity.h
	${CC} -c MadEnemy.cpp -o ${BUILD_DIR}/MadEnemy.o

${BUILD_DIR}/MiniTurtle.o: MiniTurtle.cpp MiniTurtle.h LiveEntity.h
	${CC} -c MiniTurtle.cpp -o ${BUILD_DIR}/MiniTurtle.o

${BUILD_DIR}/platform.o: platform.cpp platform.h GameEntity.h
	${CC} -c platform.cpp -o ${BUILD_DIR}/platform.o

${BUILD_DIR}/read_map.o: read_map.cpp read_map.h GameEntity.h
	${CC} -c read_map.cpp -o ${BUILD_DIR}/read_map.o

${BUILD_DIR}/turtix.o: turtix.cpp turtix.o LiveEntity.h
	${CC} -c turtix.cpp -o ${BUILD_DIR}/turtix.o

${BUILD_DIR}/text.o: text.cpp text.h turtix.cpp turtix.o LiveEntity.h turtix.h
	${CC} -c text.cpp -o ${BUILD_DIR}/text.o

clean: 
	rm *.o a.out