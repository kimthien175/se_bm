#include "Sophia.h"
#include "debug.h"

void Sophia::GetBoundingBox(float& left, float& top, float& right, float& bottom) {}

void Sophia::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	switch (state) {
		case SOPHIA_STATE_ACCELERATE_LEFT:
			vx -= SOPHIA_HORIZONTAL_ACCELERATION * dt;
			if (vx < -SOPHIA_HORIZONTAL_SPEED)
				vx = -SOPHIA_HORIZONTAL_SPEED;

			break;

		case SOPHIA_STATE_ACCELERATE_RIGHT:
			vx += SOPHIA_HORIZONTAL_ACCELERATION * dt;

			if (vx > SOPHIA_HORIZONTAL_SPEED)
				vx = SOPHIA_HORIZONTAL_SPEED;

			break;

		case SOPHIA_STATE_STOP_ACCELERATING:
			if (isMovingLeft()) {
				vx += SOPHIA_HORIZONTAL_ACCELERATION * dt;
				if (vx > 0) vx = 0;
			}
			else if (isMovingRight()) {
				vx -= SOPHIA_HORIZONTAL_ACCELERATION * dt;
				if (vx < 0) vx = 0;
			}
			break;
	}

	UpdateActions(dt);

	// Landing on platform
	if (!_isOnPlatform) {
		vy -= SOPHIA_GRAVITATIONAL_ACCELERATION * dt;
	}

	x += vx * dt;
	y += vy * dt;

	FixStandingOnPlatform();
}

void Sophia::SetRotation() {
	_isRotating = true;
	elapsedRotTime = 0;
	rotArea = 0;
}

void Sophia::UpdatePointingUp(DWORD dt) {
	if (_isAcceleratingPointingUp) {
		if (pointingStep < 4) {

			_isPointingUp = true;
			elapsedPointingTime += dt;

			if (elapsedPointingTime < SOPHIA_POINTING_UP_FRAMETIME) return;

			if (elapsedPointingTime < SOPHIA_POINTING_UP_FRAMETIME * 3) {
				pointingStep = 1;
				return;
			}

			if (elapsedPointingTime < SOPHIA_POINTING_UP_FRAMETIME * 5) {
				pointingStep = 2;
				return;
			}

			if (elapsedPointingTime < SOPHIA_POINTING_UP_FRAMETIME * 7) {
				pointingStep = 3;
				return;
			}

			pointingStep = 4;
			elapsedPointingTime = SOPHIA_POINTING_UP_FRAMETIME * 8;
		}
	}
	else if (_isPointingUp) {
		// release and set up as new
		elapsedPointingTime -= dt;

		if (elapsedPointingTime < SOPHIA_POINTING_UP_FRAMETIME) {
			_isPointingUp = false;
			elapsedPointingTime = 0;
			pointingStep = 0;

			return;
		}

		if (elapsedPointingTime < SOPHIA_POINTING_UP_FRAMETIME * 3) {
			pointingStep = 1;
			return;
		}

		if (elapsedPointingTime < SOPHIA_POINTING_UP_FRAMETIME * 5) {
			pointingStep = 2;
			return;
		}

		if (elapsedPointingTime < SOPHIA_POINTING_UP_FRAMETIME * 7) {
			pointingStep = 3;
			return;
		}
	}
}

void Sophia::UpdateRotation(DWORD dt) {
	if (_isRotating) {
		elapsedRotTime += dt;

		// angle smaller than pi/6
		if (elapsedRotTime < SOPHIA_ROT_FRAMETIME) return;

		// angle smaller than pi/2
		if (elapsedRotTime < SOPHIA_ROT_FRAMETIME * 3) {
			if (rotArea > 0) return;
			rotArea = 1;

			isFrameRot = true;
			return;
		}

		// angel small than 5pi/6
		if (elapsedRotTime < SOPHIA_ROT_FRAMETIME * 5) {
			if (rotArea > 1) return;
			rotArea = 2;

			isFrameRot = true;
			_isLookingLeft = !_isLookingLeft;
			return;
		}

		// else if elapsedRotTime < SOPHIA_ROT_FRAMETIME * 3

		isFrameRot = false;
		_isRotating = false;
	}
}

void Sophia::UpdateWheelIndex() {
	if (vx < 0) {
		// update wheel
		spNow = GetTickCount64();
		if (spWheelCurrentFrame == -1) {
			spWheelCurrentFrame = 0;
			spWheelLastFrameTime = spNow;
		}
		else {
			if (spNow - spWheelLastFrameTime > SOPHIA_WHEELS_FRAMETIME) {
				spWheelLastFrameTime = spNow;

				// CHANGE WHEEL INDEX
				wheelIndex = wheelIndex - 1;
				if (wheelIndex < 0) wheelIndex += 4;
			}
		}

		return;
	}
	else if (vx > 0) {
		// update wheel
		spNow = GetTickCount64();
		if (spWheelCurrentFrame == -1) {
			spWheelCurrentFrame = 0;
			spWheelLastFrameTime = spNow;
		}
		else {
			if (spNow - spWheelLastFrameTime > SOPHIA_WHEELS_FRAMETIME) {
				spWheelLastFrameTime = spNow;

				// CHANGE WHEEL INDEX
				wheelIndex = (wheelIndex + 1) % 4;
			}
		}

		return;
	}
}

// There are 4 frames of wheels 0->3

void Sophia::UpdateActions(DWORD dt) {

	UpdateWheelIndex();

	UpdateOscillationHeight(dt);

	UpdateRotation(dt);

	UpdatePointingUp(dt);

	UpdateJump(dt);

	spriteRowSetID = _isOnPlatform ? (
		_isPointingUp ?
		SwitchPointingUpFrame()
		:
		(isOscillationHeightLow ?
			(isFrameRot ? ID_SPRITE_SOPHIA_MED_ROT : ID_SPRITE_SOPHIA_MED) :
			(isFrameRot ? ID_SPRITE_SOPHIA_HIGH_ROT : ID_SPRITE_SOPHIA_HIGH)
			)
		)

		: ID_SPRITE_SOPHIA_HIGH;
}

int Sophia::SwitchPointingUpFrame() {
	switch (pointingStep) {
		case 0:
			return ID_SPRITE_SOPHIA_HIGH;
		case 1:
			return ID_SPRITE_SOPHIA_HIGH_DIA;
		case 2:
			return ID_SPRITE_SOPHIA_HIGHER_DIA;
		case 3:
			return ID_SPRITE_SOPHIA_HIGHEST_DIA;
		case 4:
			if (isOscillationHeightLow) return ID_SPRITE_SOPHIA_LOOK_UP_LOW;
			return ID_SPRITE_SOPHIA_LOOK_UP;
	}

	// default
	return ID_SPRITE_SOPHIA_HIGH;
}

void Sophia::FixStandingOnPlatform() {
	halfHeight = (FLOAT)(CSprites::GetInstance()->Get(spriteRowSetID)->getHeight()) / 2.0f;

	if (_isOnPlatform) {
		if (floor(y - halfHeight) - platformHeight != -1) {
			y = platformHeight + halfHeight;
		}
	}
	else {
		if (floor(y - halfHeight) - platformHeight < -1) {
			y = platformHeight + halfHeight;
			vy = 0;
			_isOnPlatform = true;
		}
	}
}

// below steps occur while isJumping, but step 1 & 4 occur while _isOnPlatform
// low:1 -> JUMP:2 -> MED (TOP):3 -> LOW (ON LANDING):4 
void Sophia::UpdateJump(DWORD dt) {
	if (isJumping) {
		if (jumpStep < 3) {
			elapsedJumpTime += dt;

			if (elapsedJumpTime < SOPHIA_JUMP_STEP_TIME) {
				jumpStep = 1;
				return;
			}

			if (elapsedJumpTime < SOPHIA_JUMP_STEP_TIME * 2) {
				jumpStep = 2;
				vy = SOPHIA_JUMP_SPEED;
				_isOnPlatform = false;
				return;
			}

			jumpStep = 3;
			elapsedJumpTime = 0;
		}
		else if (_isOnPlatform) {
			elapsedJumpTime += dt;
			jumpStep = 4;
			if (elapsedJumpTime > SOPHIA_JUMP_STEP_TIME) {
				isJumping = false;
			}
		}
	}
}

void Sophia::SetJump() {
	isJumping = true;
	jumpStep = 0;
	elapsedJumpTime = 0;
}

void Sophia::UpdateOscillationHeight(DWORD dt) {
	if (vx != 0 && _isOnPlatform) isOscillationHeightLow = wheelIndex % 2 != 0;
	else  isOscillationHeightLow = false;
}

void Sophia::Render() {
	CSprites::GetInstance()->Get(_isLookingLeft ? (spriteRowSetID + wheelIndex) : (spriteRowSetID + wheelIndex + 4))->Draw(x, y);
}
