//#include "Camera.h"
//#include "Game.h"
//
//Camera::Camera() {
//	D3DXMatrixIdentity(&World);
//	D3DXMatrixLookAtLH(&View, &Position, &Target, &Up);
//
//	//fxWVPVar = FX->GetVariableByName("WVP")->AsMatrix();
//}
//
//Camera* Camera::GetInstance() {
//	if (_instance == NULL) _instance = new Camera();
//	return _instance;
//}
//
//void Camera::Update() {
//	//D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, 0);
//	//D3DXVec3TransformCoord(&Target, &DefaultForward, &rotationMatrix);
//	//D3DXVec3Normalize(&Target, &Target);
//
//	//D3DXMATRIX RotateYTempMatrix;
//	//D3DXMatrixRotationY(&RotateYTempMatrix, yaw);
//
//	//D3DXVec3TransformNormal(&Right, &DefaultRight, &RotateYTempMatrix);
//	//D3DXVec3TransformNormal(&Up, &Up, &RotateYTempMatrix);
//	//D3DXVec3TransformNormal(&Forward, &DefaultForward, &RotateYTempMatrix);
//
//	//Position += moveLeftRight * Right;
//	//Position += moveBackForward * Forward;
//
//	//moveLeftRight = 0.0f;
//	//moveBackForward = 0.0f;
//
//	Target = Position + Target;
//
//	D3DXMatrixLookAtLH(&View, &Position, &Target, &Up);
//}
//
//Camera::~Camera() {
//	if (FX) FX->Release();
//}
//
//void Camera::SetWhenRender() {
//
//	D3DXMatrixPerspectiveFovLH(&Projection, 0.4f * 3.14f, CGame::GetInstance()->GetBackBufferWidth() / CGame::GetInstance()->GetBackBufferHeight(), 1.0f, 1000.0f);
//
//	WVP = World * View * Projection;
//	fxWVPVar->SetMatrix((float*)&WVP);
//}
