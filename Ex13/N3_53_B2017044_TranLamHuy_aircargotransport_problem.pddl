(define (problem pb1)
    (:domain air-cargo)
    (:objects C1 C2 P1 P2 SFO JKF)
    (:init 
        (Cargo C1)(Cargo C2)(Plane P1)(Plane P2)
        (Airport SFO)(Airport JKF)
        (At C1 SFO)(At C2 JKF)(At P1 SFO)(At P2 JKF)
    )
    (:goal (and (At C1 JKF)(At C2 SFO))))