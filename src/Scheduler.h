/**
File: Scheduler.h
*/

#pragma once


#include <set>
#include <stdexcept>
#include "ITask.h"
#include "ScheduledItem.h"


	//!
	//! Clase Scheduler (Programador). Permite planificar Tareas, que ser�n ejecutadas
	//! al pasar determinado tiempo. El tiempo de la clase es relativo. La clase est�
	//! optimizada para la ejecuci�n e inserci�n de tareas. 
	//!
	class Scheduler
	{
		unsigned long lastID;

		unsigned long mCurrentTime;
		std::set< ScheduledItem::Ptr, ScheduledItem::LessThanFunctor> mSet;

		//! Funci�n privada.
		//! Genera una nueva ID de Tarea. Las IDs deben ser �nicas dentro del
		//! mismo Scheduler. Entre otras cosas, sirven para diferenciar a los
		//! objetos ScheduledItem que tienen el mismo tiempo de ejecuci�n y
		//! la misma prioridad, permiti�ndo ordenarlos estrictamente.
		unsigned long GenerateNewID();

		//! Funci�n privada.
		//! Ejecuta las Tareas que debe. Llamado por Update().
		void RunDueTasks();

	public:

		typedef int TaskID;


		class Exception : public std::runtime_error
		{
		public:
			Exception(std::string const & msg) : std::runtime_error(msg) { }
		};


		//! Inicializa el Scheduler, opcionalmente con un tiempo concreto.
		//!
		//! @param curtime Tiempo actual. Es relativo as� que puede ser dado 
		//! en cualquier unidad.
		Scheduler(unsigned long curtime = 0);

		//! Asigna un valor al tiempo interno.
		//!
		void SetInternalTime(unsigned long curtime);


		//! A�ade una nueva tarea al Scheduler. Las tareas deben heredar de ITask.
		//! La primera ejecuci�n tendr� lugar despu�s de que pase el n�mero de unidades
		//! de tiempo especificadas por el par�metro wait. 
		//!
		//! @param task Puntero a la Tarea a ejecutar.
		//!
		//! @param wait Tiempo a esperar antes de ejecutar la Tarea por primera vez.
		//!
		//! @param times N�mero de veces a ejecutar la Tarea, esperando inicialmente
		//! seg�n wait y tras cada vez adicional, seg�n frequency.
		//!
		//! @param frequency Tiempo a esperar tras cada ejecuci�n para la siguiente.
		//! Si toma el valor ITask::FREQ_ASWAIT se considera que la frecuencia es la
		//! de wait.
		//!
		//! @param priority La prioridad puede ser PRIORITY_LOW, PRIORITY_NORMAL, 
		//! PRIORITY_HIGH, o cualquier n�mero, siendo las prioridades negativas las m�s 
		//!	bajas. 
		//!
		//! @return Un TaskID identificando la Tarea.
		//!
		//! @remark Una tarea no se ejecuta nunca m�s de una vez por ciclo (Update).
		//! En caso de que el delta exceda la frecuencia, la Tarea se ejecutar�
		//! al siguiente ciclo, o a los siguientes, hasta llegar al n�mero de veces
		//! apropiado.
		TaskID AddTask(ITask::Ptr const & task, unsigned long wait, long times = 1,
			long frequency = ITask::FREQ_ASWAIT, int priority = ITask::PRIORITY_NORMAL );


		//! Quita una Tarea del Scheduler, utilizando el identificador de Tarea 
		//! (TaskID).
		//! @param taskID El TaskID devuelto al a�adir la Tarea.
		void RemoveTask(TaskID taskID);


		//! Inicializa al tiempo especificado.
		//!
		//! @param time El tiempo, en cualquier unidad.
		void Initialize(unsigned long const & time);

		//! Actualiza el Scheduler, actualizando el tiempo y ejecutando todas
		//! aquellas tareas pendientes.
		//!
		//! @param delta Un incremento de tiempo, generalmente el incremento de
		//! tiempo pasado desde la �ltima llamada a este mismo Update.
		//!
		//! @remark Una tarea no se ejecuta nunca m�s de una vez por ciclo (Update).
		//! En caso de que el delta exceda la frecuencia, la Tarea se ejecutar�
		//! al siguiente ciclo, o a los siguientes, hasta llegar al n�mero de veces
		//! apropiado.
		void Update(unsigned long const & delta);


		//! Ejecuta las tareas pendientes sin modificar el cron�metro interno.
		//!
		void RunPendingTasksOnly();


		//! Solamente actualiza el cron�metro interno mediante un incremento,
		//! sin ejecutar ninguna tarea pendiente.
		//!
		void UpdateOnly(unsigned long const & delta);

	};
